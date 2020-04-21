#include "../top.h"

int top() {
	FASTQ_LINE fastQLine;
	FASTA_LINE fastaLine;
	SAM_LINE samLine;

	//RESERVE MEMORY
	BASE *addrSpaceReverseSeq = 0;
	initSeq(&(fastQLine.seq.el), &addrSpaceReverseSeq);
	initRef(&(fastaLine.ref.el));
	CELL *addrSpaceMatrix = 0;
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	//LOAD THE REF
	loadRef(fastaPath, &fastaLine);
	displayFASTAline(fastaLine);

	//OPEN THE FILES:
	FILE* fastQfile = fopen(fastQPath, "r");
	FILE* samFile = fopen(samPath, "w+");

	if(fastQfile == NULL || samFile == NULL){
		printf("ERROR: Files didn't open correctly");
		fclose(fastQfile);
		fclose(samFile);
		sds_free(fastQLine.seq.el);
		sds_free(fastaLine.ref.el);
		sds_free(addrSpaceMatrix);

		return -1;
	}

	//INIT THE SW MATRIX:
	initMatrix(refMax, seqMax, addrSpaceMatrix);

	/////////////////////////////////

	int counter = 1;
	FASTQ_LINE revFastQ;

	int allReadsDone = 0;
	do {
		allReadsDone = readNextFastqLine(fastQfile, &fastQLine);
		//displayCurrFASTQline(fastQLine); //debug

		//PERFORM MAPPING
		FASTQ_LINE* fastQ = align(fastaLine, &fastQLine, &samLine, addrSpaceMatrix, addrSpaceReverseSeq, &revFastQ);
		samLine.fastQLine = *fastQ;

		//displayCurrSAMline(samLine); //debug
		printf("%i: sequence: %s\t => flag: %i\n", counter, fastQLine.Qname, samLine.Flag);

		writeSamLine(samFile, samLine);
		counter++;
	} while (allReadsDone != 255);

	/////////////////////////////////

	//CLOSE THE FILES
	fclose(fastQfile);
	fclose(samFile);
	printf("files saved\n");

	//FREE THE MEMORY
	sds_free(fastQLine.seq.el);
	sds_free(fastaLine.ref.el);
	sds_free(addrSpaceMatrix);

	return 0;
}
