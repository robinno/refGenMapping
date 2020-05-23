#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "displayForDebug.h"
#include "../PARAMS.h"
#include "../TYPES.h"

#include <stdio.h>//for sprintf function
#include <string.h>//for strcat function

/**
 * Fills in the matrix' first row and column with zeros
 *
 * @param refLength: the length of the reference sequence
 * @param seqLength: the length of the sequence to match
 * @param matrix: array (1D) of the required length to fill in, in physical memory
 */
void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix);

/**
 * Fills in the matrix according to the Smith-Waterman algorithm
 *
 * @param ref: the reference sequence
 * @param seq: the sequence to match
 * @param matrix: array (1D) of the required length to fill in, in physical memory
 *
 * @return the position of the maximum cell in the matrix
 */
POS FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]);

#endif
