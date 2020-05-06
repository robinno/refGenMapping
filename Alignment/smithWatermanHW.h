#ifndef SMITHWATERMANHW_H
#define SMITHWATERMANHW_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#pragma SDS data access_pattern(ref:SEQUENTIAL, seq:SEQUENTIAL, matrix:SEQUENTIAL)
#pragma SDS data sys_port(ref:AFI, seq:AFI, matrix:AFI)
#pragma SDS data mem_attribute(ref:PHYSICAL_CONTIGUOUS, seq:PHYSICAL_CONTIGUOUS, matrix:PHYSICAL_CONTIGUOUS)
#pragma SDS data zero_copy(ref[0:sliceSize], seq[0:seqMax], matrix[0:seqMax*sliceSize])
MATRIX_INDEX FillInHW(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax], SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]);


#endif
