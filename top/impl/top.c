#include "../top.h"

int top() {
	BASE *seq = 0;
	BASE *ref = 0;
	CELL *addrSpaceMatrix = 0;

	initSeq(&seq);
	initRef(&ref);
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	REF_INDEX refLength = loadRef(ref);

	FILE* seqFastQ = openFileSeqRead();
	SEQ_INDEX seqLength;

	int allReadsDone = 0;
	do{
		allReadsDone = loadNextSeq(seqFastQ, seq, &seqLength);
	}while(allReadsDone != 255);

//	initSmithWaterman(refLength, seqLength, addrSpaceMatrix); //init alignment matrix
//	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	closeFileSeqRead(seqFastQ);

	sds_free(seq);
	sds_free(ref);
	sds_free(addrSpaceMatrix);

	return 0;
}
