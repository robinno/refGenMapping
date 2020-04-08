#include "topheaders/top.h"

int top(){
	BASE *seq = 0;
	BASE *ref = 0;
	REF_INDEX refLength;
	SEQ_INDEX seqLength;

	initMem(seq, ref, &seqLength, &refLength);

	smithWaterman(ref, refLength, seq, seqLength);//perform test

	free_memory(ref);

	return 0;
}
