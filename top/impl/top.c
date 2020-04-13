#include "../top.h"

int top() {
	SEQ_READ seq_input;

	BASE *ref = 0;
	CELL *addrSpaceMatrix = 0;

	initSeq(&(seq_input.seq.el));
	initRef(&ref);
	initAlignMatrixAddrSpace(&addrSpaceMatrix);

	REF_INDEX refLength = loadRef(ref);

	FILE* seqFastQFile = openFileSeqRead();

	int allReadsDone = 0;
	do{
		allReadsDone = loadNextSeq(seqFastQFile, &seq_input);
		displayCurrSeq(seq_input);
	}while(allReadsDone != 255);

//	initSmithWaterman(refLength, seqLength, addrSpaceMatrix); //init alignment matrix
//	smithWaterman(ref, refLength, seq, seqLength, addrSpaceMatrix); //perform SW

	closeFileSeqRead(seqFastQFile);

	sds_free(seq_input.seq.el);
	sds_free(ref);
	sds_free(addrSpaceMatrix);

	return 0;
}
