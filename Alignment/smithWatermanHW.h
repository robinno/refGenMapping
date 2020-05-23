#ifndef SMITHWATERMANHW_H
#define SMITHWATERMANHW_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"


/**
 * Fills in the matrix according to the Smith-Waterman algorithm
 *
 * @param ref: array of the reference sequence, in physical memory
 * @param refLength: length of ref array
 * @param seq: array of the sequence to match, in physical memory
 * @param seqLength: length of seq array
 * @param matrix: array (1D) of the required length to fill in, in physical memory
 *
 * @return the position of the maximum cell in the matrix
 */
#pragma SDS data access_pattern(ref:SEQUENTIAL, seq:SEQUENTIAL, matrix:SEQUENTIAL)
#pragma SDS data sys_port(ref:AFI, seq:AFI, matrix:AFI)
#pragma SDS data mem_attribute(ref:PHYSICAL_CONTIGUOUS, seq:PHYSICAL_CONTIGUOUS, matrix:PHYSICAL_CONTIGUOUS)
#pragma SDS data zero_copy(ref[0:refMax], seq[0:seqMax], matrix[0:refMax*seqMax])
MATRIX_INDEX FillInHW(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax], SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]);

#endif
