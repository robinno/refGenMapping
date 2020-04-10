#include "../initMem.h"

int initSeq(BASE** seq) {
	//in physical memory
	*seq = (BASE *) sds_alloc(sizeof(BASE) * seqMax);

	if (seq) {
		sds_free(seq);
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

