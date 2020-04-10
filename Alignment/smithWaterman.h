#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "sds_lib.h" //for sds_alloc function

void initSmithWaterman(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix);

CELL* smithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]);

//////////////////////
//PRIVATE functions://

CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos);
CELL_VALUE sim(BASE a, BASE b);
MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column);

#endif
