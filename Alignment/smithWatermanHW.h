#ifndef SMITHWATERMANHW_H
#define SMITHWATERMANHW_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#include <stdio.h>//for sprintf function
#include <string.h>//for strcat function

POS FillInMatrixHW(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);

#endif
