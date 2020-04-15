#include "../SAM_interface.h"

void initSamLine(SAM_LINE* samLine){
	//initialize defaults
	samLine->Rnext[0] = '*';
	samLine->Pnext = 0;
	samLine->Tlen = 0;
}

FILE* openSamFile(){
	FILE* fp = fopen(samPath, "w+");
	return fp;
}

void closeSamFile(FILE* fp){
	fclose(fp);
}

void displaySamLine(SAM_LINE samLine){

	printf("%s\t", samLine.fastQLine.Qname);
	printf("%i\t", samLine.Flag);
	printf("%s\t", samLine.fastALine.Rname);
	printf("%i\t", samLine.Pos);
	printf("%i\t", samLine.MapQ);
	printf("%s\t", samLine.CIGAR);
	printf("%s\t", samLine.Rnext);
	printf("%i\t", samLine.Pnext);
	printf("%i\t", samLine.Tlen);

	//print sequence
	for(SEQ_INDEX i = 0; i < samLine.fastQLine.seq.length; i++){
		printf("%c", baseToChar(samLine.fastQLine.seq.el[i]));
	}
	printf("\t");

	printf("%s\t", samLine.fastQLine.qualities);

	printf("\n");
}

void writeSamLine(FILE* fp, SAM_LINE samLine){

	fprintf(fp, "%s\t", samLine.fastQLine.Qname);
	fprintf(fp, "%i\t", samLine.Flag);
	fprintf(fp, "%s\t", samLine.fastALine.Rname);
	fprintf(fp, "%i\t", samLine.Pos);
	fprintf(fp, "%i\t", samLine.MapQ);
	fprintf(fp, "%s\t", samLine.CIGAR);
	fprintf(fp, "%s\t", samLine.Rnext);
	fprintf(fp, "%i\t", samLine.Pnext);
	fprintf(fp, "%i\t", samLine.Tlen);

	//print sequence
	for(SEQ_INDEX i = 0; i < samLine.fastQLine.seq.length; i++){
		fputc(baseToChar(samLine.fastQLine.seq.el[i]), fp);
	}
	fputc('\t', fp);

	fprintf(fp, "%s\t", samLine.fastQLine.qualities);

	fprintf(fp, "\n");
}
