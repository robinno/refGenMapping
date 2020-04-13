#include <stdio.h>
#include <stdlib.h>

#include "../../PARAMS.h"
#include "functions.h" //for the charToBase function

#define seqPath "/mnt/reads.fastq"

FILE* openFileSeqRead();
int loadNextSeq(FILE* fp, SEQ_READ* seq);
void closeFileSeqRead(FILE* fp);

//PRIVATE FUNCTIONS
int readQName(FILE* fp, SEQ_READ* seq);
int readSeq(FILE* fp, SEQ_READ* seq);
int readCertainties(FILE* fp, SEQ_READ* seq);
int nextLineOfFile(FILE* fp);
