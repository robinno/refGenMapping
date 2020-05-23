#ifndef ALIGN_H
#define ALIGN_H

#include "../PARAMS.h"
#include "../TYPES.h"
#include "smithWaterman.h"
#include "smithWatermanHW.h"

/**
 * Aligns the sequence in both forward and reverse way and pick's the best option.
 * The full MAPPED_READ-type will be filled in.
 *
 * @param genome: the reference sequence
 * @param read: the FASTQ information of the sequence to match
 * @param mapped_read: a pointer to the mapped_read type to be filled in
 * @param addrSpaceMatrix: array (1D) of the required length to fill in, in physical memory
 * @param addrSpaceReverseSeq: pointer to reserved memory for the reversed sequence
 * @param revRead: the reverse sequence FASTQ information
 */
void align(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead);

/**
 * displays the first 15 rows and columns of the matrix on the screen,
 * as well as the corresponding reference and sequence
 *
 * @param ref: the reference sequence
 * @param seq: the sequence to match
 * @param matrix: array (1D) of the required length to fill in, in physical memory
 */
void alignHW(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead);


/**
 * PRIVATE FUNCTION:
 * fills in the reverse sequence address space with the complementary
 *
 * @param LeftToRight: the FASTQ information of the sequence
 * @param RightToLeft: the reverse FASTQ information
 * @param addrSpaceReverseSeq: address space reserved for the reverse sequence
 */
void reverseSeq(READ LeftToRight, READ* RightToLeft, BASE* addrSpaceReverseSeq);

/**
 * PRIVATE FUNCTION:
 * Generates the CIGAR string from the filled in matrix and the maximum position
 *
 * @param CIGAR: an array of chars where the finished CIGAR string should be stored
 * @param matrix: the filled in matrix by Smith-Waterman
 * @param maxPos: Position of the maximum in the matrix
 *
 * @return 0 if a full CIGAR was generated;
 * 		-1 if the CIGAR would be too long according to maxCigarParts parameter
 */
int generateCIGAR(char* CIGAR, CELL* matrix, POS maxPos);

/**
 * PRIVATE FUNCTION:
 * Generates the mapping quality from the length of the sequence and the maximum value
 *
 * @param mapQ: returned mapping quality
 * @param max_value: max value in the matrix filled in by Smith-Waterman
 * @param seqLength: length of the sequence used to fill in the matrix
 */
void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength);

#endif
