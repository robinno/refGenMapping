#ifndef DISPLAYFORDEBUG_H
#define DISPLAYFORDEBUG_H

#include <stdio.h>

#include "../TYPES.h"

/**
 * displays the first 15 rows and columns of the matrix on the screen,
 * as well as the corresponding reference and sequence
 *
 * @param ref: the reference sequence
 * @param seq: the sequence to match
 * @param matrix: array (1D) of the required length to fill in, in physical memory
 */
void displayMatrix(REF ref, SEQ seq, CELL matrix[seqMax * refMax]);

/**
 * displays the maximum value and position
 *
 * @param maxPos: position of the maximum
 * @param max: value of the maximum
 */
void displayMax(POS maxPos, CELL_VALUE max);

#endif
