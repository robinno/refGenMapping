#include "../top.h"


int top() {
	READ read;
	GENOME genome;
	MAPPED_READ mapped_read;

	//RESERVE MEMORY
	BASE *addrSpaceReverseSeq = 0;
	initSeq(&(read.seq.el), &addrSpaceReverseSeq);
	initRef(&(genome.ref.el));
	CELL *addrSpaceMatrix = 0;
	//#pragma HLS data_pack variable=addrSpaceMatrix struct_level //needed for hardware acceleration
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	//INIT THE SW MATRIX:
	initMatrix(refMax, seqMax, addrSpaceMatrix);

	//LOAD THE REF
	loadGenome(fastaPath, &genome);
	displayGenomeInfo(genome);

	//OPEN THE FILES:
	FILE* fastQfile = fopen(fastQPath, "r");
	FILE* samFileSW = fopen(samPathSW, "w+");
	FILE* samFileHW = fopen(samPathHW, "w+");

	if (fastQfile == NULL || samFileSW == NULL || samFileHW == NULL) {
		printf("ERROR: Files didn't open correctly");
		fclose(fastQfile);
		fclose(samFileSW);
		fclose(samFileHW);
		sds_free(read.seq.el);
		sds_free(genome.ref.el);
		sds_free(addrSpaceMatrix);

		return -1;
	}

	/////////////////////////////////

	int counter = 1;
	READ revRead;

	//performance counters:
	perf_counter sw_ctr, hw_ctr;
	PCreset(&sw_ctr);
	PCreset(&hw_ctr);

	int allReadsDone = 0;
	do {
		allReadsDone = loadNextRead(fastQfile, &read);
		//displayCurrReadInfo(read); //debug

		//SOFTWARE
		PCstart(&sw_ctr);
		align(genome, &read, &mapped_read, addrSpaceMatrix, addrSpaceReverseSeq,
				&revRead);
		PCstop(&sw_ctr);

		//displayCurrMappedReadInfo(mapped_read); //debug
//		printf("%i: in software => sequence: %s\t => flag: %i\n", counter, read.Qname,
//				mapped_read.Flag);
		writeSamLine(samFileSW, mapped_read);

		//HARDWARE
		PCstart(&hw_ctr);
		alignHW(genome, &read, &mapped_read, addrSpaceMatrix,
				addrSpaceReverseSeq, &revRead);
		PCstop(&hw_ctr);

		//displayCurrMappedReadInfo(mapped_read); //debug
//		printf("%i: in hardware => sequence: %s\t => flag: %i\n", counter, read.Qname,
//				mapped_read.Flag);
		writeSamLine(samFileHW, mapped_read);

		printf("%i: sequence: %s\t => flag: %i\n", counter, read.Qname, mapped_read.Flag);
		counter++;
		printf("current clock: %"PRIu64"\n", (uint64_t) sds_clock_counter());
	} while (allReadsDone != 255);

	unsigned long long sw_cycles = avg_cpu_cycles(sw_ctr);
	unsigned long long hw_cycles = avg_cpu_cycles(hw_ctr);
	double speedup = (double) sw_cycles / (double) hw_cycles;

	printf("Average number of CPU cycles running in software: %llu\n", sw_cycles);
	printf("Average number of CPU cycles running in hardware: %llu\n", hw_cycles);
	printf("speedup: %f\n", speedup);

	/////////////////////////////////

	//CLOSE THE FILES
	fclose(fastQfile);
	fclose(samFileSW);
	fclose(samFileHW);
	printf("files saved\n");

	//FREE THE MEMORY
	sds_free(read.seq.el);
	sds_free(genome.ref.el);
	sds_free(addrSpaceMatrix);

	return 0;
}
