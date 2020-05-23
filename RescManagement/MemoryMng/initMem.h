#ifndef INITMEM_H
#define INITMEM_H

#include "../../PARAMS.h"
#include "../../TYPES.h"

#include "sds_lib.h" //for sds_alloc function

/**
 * reserves space for the sequence (forward and reserve).
 * Size is determined in the PARAMS.h file.
 * will store pointers to the reserved memory location at the given pointers
 */
int initSeq(BASE** LRseq, BASE** RLseq);

/**
 * reserves space for the reference.
 * Size is determined in the PARAMS.h file.
 * will store pointer to the reserved memory location at the given pointer
 */
int initRef(BASE** ref);

/**
 * reserves space for the matrix.
 * Size is determined in the PARAMS.h file.
 * will store pointers to the reserved memory location at the given pointers
 */
int initAlignMatrixAddrSpace(CELL** matrix);

#endif
