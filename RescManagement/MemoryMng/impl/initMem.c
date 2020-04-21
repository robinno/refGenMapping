#include "../initMem.h"

int initSeq(BASE** LRseq, BASE** RLseq) {
	//in physical memory
	*LRseq = (BASE *) sds_alloc(sizeof(BASE) * seqMax);
	*RLseq = (BASE *) sds_alloc(sizeof(BASE) * seqMax);

	if (LRseq) {
		sds_free(LRseq);
		return -1;
	} else if (RLseq) {
		sds_free(RLseq);
		return -1;
	} else {
		return 0;
	}
}

int initRef(BASE** ref) {
	//in physical memory
	*ref = (BASE *) sds_alloc(sizeof(BASE) * refMax);

	if (ref) {
		sds_free(ref);
		return -1;
	} else {
		return 0;
	}
}

int initAlignMatrixAddrSpace(CELL** matrix) {
	//INIT MATRIX (in physical memory)
	*matrix = (CELL *) sds_alloc(sizeof(CELL) * seqMax * refMax);

	if (matrix) {
		sds_free(matrix);
		return -1;
	} else {
		return 0;
	}
}

