#include "../PARAMS.h"
#include "../TYPES.h"
#include "smithWaterman.h"

void align(FASTA_LINE fastaLine, FASTQ_LINE fastqLine, SAM_LINE* samLine, CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq);
void reverseSeq(SEQ LeftToRight, SEQ* RightToLeft, BASE* addrSpaceReverseSeq);

void generateCIGAR(char* CIGAR, CELL* LL);
void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength);
