#ifndef DISPLAYFORDEBUG_H
#define DISPLAYFORDEBUG_H

#include <stdio.h>

#include "../TYPES.h"

void displayMatrix(REF ref, SEQ seq, CELL matrix[seqMax * refMax]);
void displayLL(CELL* cell);
void displayMax(POS maxPos, CELL_VALUE max);

#endif
