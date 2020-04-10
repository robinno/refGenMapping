#ifndef DISPLAYFORDEBUG_H
#define DISPLAYFORDEBUG_H

#include <stdio.h>

#include "../PARAMS.h"

void displayMatrix(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[seqMax * refMax]);
void displayLL(CELL* cell);
void displayMax(POS maxPos, CELL_VALUE max);

#endif
