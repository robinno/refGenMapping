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
	displayFASTAline(fastaLine);
	samLine.fastALine = fastaLine;

	//OPEN THE FILES:
	FILE* fastQfile = fopen(fastQPath, "r");
	FILE* samFile = fopen(samPath, "w+");

	//INIT THE SW MATRIX:
	initMatrix(refMax, seqMax, addrSpaceMatrix);

	/////////////////////////////////

	int allReadsDone = 0;
	do {
		allReadsDone = readNextFastqLine(fastQfile, &fastQLine);
		displayCurrFASTQline(fastQLine);

		//PERFORM MAPPING
		CELL* maxCell = FillInMatrix(fastaLine.ref, fastQLine.seq, addrSpaceMatrix);

		generateCIGAR(samLine.CIGAR, maxCell);

		samLine.fastQLine = fastQLine;
		displayCurrSAMline(samLine);
		writeSamLine(samFile, samLine);
	} while (allReadsDone != 255);

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
