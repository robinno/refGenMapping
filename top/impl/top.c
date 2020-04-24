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
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	//INIT THE SW MATRIX:
	initMatrix(refMax, seqMax, addrSpaceMatrix);

	//LOAD THE REF
	loadGenome(fastaPath, &genome);
	displayGenomeInfo(genome);

	//OPEN THE FILES:
	FILE* fastQfile = fopen(fastQPath, "r");
	FILE* samFile = fopen(samPath, "w+");

	if (fastQfile == NULL || samFile == NULL) {
		printf("ERROR: Files didn't open correctly");
		fclose(fastQfile);
		fclose(samFile);
		sds_free(read.seq.el);
		sds_free(genome.ref.el);
		sds_free(addrSpaceMatrix);

		return -1;
	}

	/////////////////////////////////

	int counter = 1;
	READ revRead;

	int allReadsDone = 0;
	do {
		allReadsDone = loadNextRead(fastQfile, &read);
		//displayCurrReadInfo(read); //debug

		//PERFORM MAPPING
		align(genome, &read, &mapped_read, addrSpaceMatrix,
				addrSpaceReverseSeq, &revRead);

		//displayCurrMappedReadInfo(mapped_read); //debug
		printf("%i: sequence: %s\t => flag: %i\n", counter, read.Qname,
				mapped_read.Flag);

		writeSamLine(samFile, mapped_read);
		counter++;
	} while (allReadsDone != 255);

	/////////////////////////////////

	//CLOSE THE FILES
	fclose(fastQfile);
	fclose(samFile);
	printf("files saved\n");

	//FREE THE MEMORY
	sds_free(read.seq.el);
	sds_free(genome.ref.el);
	sds_free(addrSpaceMatrix);

	return 0;
}
