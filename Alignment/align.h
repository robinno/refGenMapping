#ifndef ALIGN_H
#define ALIGN_H

#include "../PARAMS.h"
#include "../TYPES.h"
#include "smithWaterman.h"

READ* align(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead);
void reverseSeq(READ LeftToRight, READ* RightToLeft, BASE* addrSpaceReverseSeq);

int generateCIGAR(char* CIGAR, CELL* LL);
void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength);

#endif
