#include "../displayInfo.h"

void displayFASTAline(FASTA_LINE fastaLine){
	printf("the reference genome:\n");
	printf("Rname: %s\n", fastaLine.Rname);
	printf("length of reference: %i\n", fastaLine.ref.length);
	printf("\n");
}

void displayCurrFASTQline(FASTQ_LINE fastqLine){
	printf("The current sequence:\n");
	printf("Qname: %s\n", fastqLine.Qname);
	printf("Sequence: \t");
	for(SEQ_INDEX i = 0; i < fastqLine.seq.length; i++){
		printf("%i", fastqLine.seq.el[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) fastqLine.seq.length);
	printf("Qualities: \t");
	for(SEQ_INDEX i = 0; i < fastqLine.seq.length; i++){
		printf("%c", fastqLine.qualities[i]);
	}
	printf("\n\n");
}

void displayCurrSAMline(SAM_LINE samLine){
	printf("The current sequence (mapped):\n");
	printf("Qname: %s\n", samLine.fastQLine.Qname);
	printf("Sequence: \t");
	for(SEQ_INDEX i = 0; i < samLine.fastQLine.seq.length; i++){
		printf("%i", samLine.fastQLine.seq.el[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) samLine.fastQLine.seq.length);
	printf("Qualities: \t");
	for(SEQ_INDEX i = 0; i < samLine.fastQLine.seq.length; i++){
		printf("%c", samLine.fastQLine.qualities[i]);
	}

	printf("Flag: %i\n", samLine.Flag);
	printf("Position found: %i\n", samLine.Pos);
	printf("Mapping qualitiy: %i\n", samLine.MapQ);
	printf("CIGAR string: %s\n", samLine.CIGAR);

	printf("\n\n");
}
