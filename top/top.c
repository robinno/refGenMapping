#include "topheaders/top.h"

int top(){
	BASE *seq = 0;
	BASE *ref = 0;
	REF_INDEX refLength;
	SEQ_INDEX seqLength;

	initMem(seq, ref, &seqLength, &refLength);

	CELL* addrSpace = initSmithWaterman(ref, refLength, seq, seqLength); //init alignment
	smithWaterman(ref, refLength, seq, seqLength, addrSpace); //perform SW

	free_memory(ref);

	return 0;
}
