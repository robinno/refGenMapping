#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#include <stdio.h>//for sprintf function
#include <string.h>//for strcat function

void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix);

POS FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);

#endif
