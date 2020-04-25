#ifndef ALIGN_H
#define ALIGN_H

#include "../PARAMS.h"
#include "../TYPES.h"
#include "smithWaterman.h"

void align(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead);

//PRIVATE FUNCTIONS:
void reverseSeq(READ LeftToRight, READ* RightToLeft, BASE* addrSpaceReverseSeq);
int generateCIGAR(char* CIGAR, CELL* matrix, POS maxPos);
void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength);

#endif
