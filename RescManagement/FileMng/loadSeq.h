#include <stdio.h>
#include <stdlib.h>

#include "../../PARAMS.h"
#include "functions.h" //for the charToBase function

#define seqPath "/mnt/reads.fastq"

FILE* openFileSeqRead();
int loadNextSeq(FILE* fp, BASE* seq, SEQ_INDEX* seqLength);
void closeFileSeqRead(FILE* fp);

//PRIVATE FUNCTION
int nextLineOfFile(FILE* fp);
