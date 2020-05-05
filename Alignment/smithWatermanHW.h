#ifndef SMITHWATERMANHW_H
#define SMITHWATERMANHW_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#define sliceSize 200

POS FillInMatrixHW(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);

#pragma SDS data access_pattern(ref:SEQUENTIAL, seq:SEQUENTIAL, matrix:SEQUENTIAL)
#pragma SDS data sys_port(ref:AFI, seq:AFI, matrix:AFI)
#pragma SDS data mem_attribute(ref:PHYSICAL_CONTIGUOUS, seq:PHYSICAL_CONTIGUOUS, matrix:PHYSICAL_CONTIGUOUS)
#pragma SDS data zero_copy(ref[0:sliceSize], seq[0:seqMax], matrix[0:seqMax*sliceSize])
void FIMHW(BASE ref[sliceSize], BASE seq[seqMax], MATRIX_INDEX seqLength,
		CELL matrix[sliceSize * seqMax], POS* maxPos, CELL_VALUE* currentMaxVal, REF_INDEX coloffset);

#endif
