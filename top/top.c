#include "topheaders/top.h"

int top(){
	BASE *seq = 0;
	BASE *ref = 0;
	REF_INDEX refLength;
	SEQ_INDEX seqLength;

	initMem(&seq, &ref, &seqLength, &refLength);

	CELL* addrSpaceMatrix = initSmithWaterman(ref, refLength, seq, seqLength); //init alignment
	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	free_memory(ref, addrSpaceMatrix);

	return 0;
}
