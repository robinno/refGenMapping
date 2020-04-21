#include "../displayInfo.h"

void displayGenomeInfo(GENOME genome) {
	printf("the reference genome:\n");
	printf("Rname: %s\n", genome.Rname);
	printf("length of reference: %i\n", genome.ref.length);
	printf("\n");
}

void displayCurrReadInfo(READ read) {
	printf("The current sequence:\n");
	printf("Qname: %s\n", read.Qname);
	printf("Sequence: \t");
	for (SEQ_INDEX i = 0; i < read.seq.length; i++) {
		printf("%i", read.seq.el[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) read.seq.length);
	printf("Qualities: \t");
	for (SEQ_INDEX i = 0; i < read.seq.length; i++) {
		printf("%c", read.qualities[i]);
	}
	printf("\n\n");
}

void displayCurrMappedReadInfo(MAPPED_READ mapped_read) {
	printf("The current sequence (mapped):\n");
	printf("Qname: %s\n", mapped_read.read.Qname);
	printf("Sequence: \t");
	for (SEQ_INDEX i = 0; i < mapped_read.read.seq.length; i++) {
		printf("%i", mapped_read.read.seq.el[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) mapped_read.read.seq.length);
	printf("Qualities: \t");
	for (SEQ_INDEX i = 0; i < mapped_read.read.seq.length; i++) {
		printf("%c", mapped_read.read.qualities[i]);
	}
	printf("\n");
	printf("Flag: %i\n", mapped_read.Flag);
	printf("Position found: %i\n", mapped_read.Pos);
	printf("Mapping qualitiy: %i\n", mapped_read.MapQ);
	printf("CIGAR string: %s\n", mapped_read.CIGAR);

	printf("\n\n");
}
