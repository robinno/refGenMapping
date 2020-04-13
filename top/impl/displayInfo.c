#include "../displayInfo.h"

void displayCurrSeq(SEQ_READ seq){
	printf("The current sequence:\n");
	printf("Qname: %s\n", seq.qname);
	printf("Sequence: \t");
	for(SEQ_INDEX i = 0; i < seq.seqLength; i++){
		printf("%i", seq.seq[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) seq.seqLength);
	printf("Certainties: \t");
	for(SEQ_INDEX i = 0; i < seq.seqLength; i++){
		printf("%c", seq.certainties[i]);
	}
	printf("\n\n");
}
