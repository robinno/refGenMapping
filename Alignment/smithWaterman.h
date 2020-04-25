#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#include <stdio.h>//for sprintf function
#include <string.h>//for strcat function

void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix);

POS FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);

//////////////////////
//PRIVATE functions://

//inline CELL generateCell(CELL diagonal, CELL left, CELL up, BASE refVal,
//		BASE seqVal);
//inline CELL_VALUE sim(BASE a, BASE b);
//inline MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column);

#endif
