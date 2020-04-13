#include "../top.h"

int top() {
	SEQ_READ seq;

	BASE *ref = 0;
	CELL *addrSpaceMatrix = 0;

	initSeq(&(seq.seq));
	initRef(&ref);
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	REF_INDEX refLength = loadRef(ref);

	FILE* seqFastQ = openFileSeqRead();

	int allReadsDone = 0;
	do{
		allReadsDone = loadNextSeq(seqFastQ, &seq);
		displayCurrSeq(seq);
	}while(allReadsDone != 255);

//	initSmithWaterman(refLength, seqLength, addrSpaceMatrix); //init alignment matrix
//	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	closeFileSeqRead(seqFastQ);

	sds_free(seq.seq);
	sds_free(ref);
	sds_free(addrSpaceMatrix);

	return 0;
}
