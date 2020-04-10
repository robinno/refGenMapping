#include "../top.h"

int top() {
	BASE *seq = 0;
	SEQ_INDEX seqLength = 10;

	BASE *ref = 0;
	REF_INDEX refLength = 9;

	CELL *addrSpaceMatrix = 0;

	initSeq(&seq);
	initRef(&ref);
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	initSmithWaterman(refLength, seqLength, addrSpaceMatrix); //init alignment matrix
	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	sds_free(seq);
	sds_free(ref);
	sds_free(addrSpaceMatrix);

	return 0;
}
