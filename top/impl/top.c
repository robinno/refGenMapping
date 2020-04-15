#include "../top.h"

int top() {
	FASTQ_LINE fastQLine;
	FASTA_LINE fastaLine;
	SAM_LINE samLine;

	//RESERVE MEMORY
	initSeq(&(fastQLine.seq.el));
	initRef(&(fastaLine.ref.el));
	CELL *addrSpaceMatrix = 0;
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	//LOAD THE REF
	loadRef(fastaPath, &fastaLine);

	//OPEN THE FILES:
	FILE* fastQfile = fopen(fastQPath, "r");
	FILE* samFile = fopen(samPath, "w+");

	/////////////////////////////////

	int allReadsDone = 0;
	do{
		allReadsDone = readNextFastqLine(fastQfile, &fastQLine);
		displayCurrSeq(fastQLine);
	}while(allReadsDone != 255);

//	initSmithWaterman(refLength, seqLength, addrSpaceMatrix); //init alignment matrix
//	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	/////////////////////////////////

	//CLOSE THE FILES
	fclose(fastQfile);
	fclose(samFile);

	//FREE THE MEMORY
	sds_free(fastQLine.seq.el);
	sds_free(fastaLine.ref.el);
	sds_free(addrSpaceMatrix);

	return 0;
}
