#include "topheaders/initMem.h"

SEQ_INDEX initSeq(BASE* seq){
	SEQ_INDEX seqLength = 10;

	//in stack memory
	BASE newSeq[seqMax] = {0, 4, 4, 2, 2, 4, 1, 3, 2, 1}; //TEST VECTOR
	seq = newSeq;

	return seqLength;
}

REF_INDEX initRef(BASE* ref){
	REF_INDEX refLength = 9; //CHANGE WHEN FILE CHANGES! (length of file + 1)

	//in physical memory
	ref = (BASE *)sds_alloc(refMax * sizeof(BASE));

	//init ref from file memory:
	FILE *fp;
	fp = fopen("/mnt/ref.txt", "r");
	ref[0] = 0; //first element = 0;
	for(REF_INDEX i = 1; i < refLength; i++){
		ref[i] = charToBase(fgetc(fp));
	}
	fclose(fp);

	return refLength;
}


int initMem(BASE* seq, BASE* ref, SEQ_INDEX* seqL, REF_INDEX* refL){
	*seqL = initSeq(seq);
	*refL = initRef(ref);

	//check for buffer overflow
	if(*seqL > seqMax)
		return -1;
	else if (*refL > refMax)
		return -2;
	else
		return 0;
}

