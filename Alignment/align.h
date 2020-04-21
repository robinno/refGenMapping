#include "../PARAMS.h"
#include "../TYPES.h"
#include "smithWaterman.h"

FASTQ_LINE* align(FASTA_LINE fastaLine, FASTQ_LINE* fastqLine, SAM_LINE* samLine,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, FASTQ_LINE* revFastQ);
void reverseSeq(FASTQ_LINE LeftToRight, FASTQ_LINE* RightToLeft,
		BASE* addrSpaceReverseSeq);

int generateCIGAR(char* CIGAR, CELL* LL);
void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength);
