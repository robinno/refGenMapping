#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "../../PARAMS.h"
#include "displayForDebug.h"
#include "sds_lib.h" //for sds_alloc function

CELL* initSmithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength);

CELL* smithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]);

//private functions:
CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos);
CELL_VALUE sim(BASE a, BASE b);
MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column);

#endif
