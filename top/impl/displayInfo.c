#include "../displayInfo.h"

void displayCurrSeq(SEQ_READ seq_input){
	printf("The current sequence:\n");
	printf("Qname: %s\n", seq_input.qname);
	printf("Sequence: \t");
	for(SEQ_INDEX i = 0; i < seq_input.seq.length; i++){
		printf("%i", seq_input.seq.el[i]);
	}
	printf("\n");
	printf("Length of sequence: %i\n", (int) seq_input.seq.length);
	printf("Certainties: \t");
	for(SEQ_INDEX i = 0; i < seq_input.seq.length; i++){
		printf("%c", seq_input.certainties[i]);
	}
	printf("\n\n");
}
