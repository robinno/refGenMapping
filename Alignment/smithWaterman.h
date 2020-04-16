#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#include <stdio.h>//for sprintf function
#include <string.h>//for strcat function

void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix);

CELL* FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);
void generateCIGAR(char* CIGAR, CELL* LL);

//////////////////////
//PRIVATE functions://

CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos);
CELL_VALUE sim(BASE a, BASE b);
MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column);

#endif
