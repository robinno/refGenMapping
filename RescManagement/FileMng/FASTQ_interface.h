#ifndef FASTQ_INF_H
#define FASTQ_INF_H

#include <stdio.h>
#include <stdlib.h>

#include "../../TYPES.h"
#include "ConversionFunctions.h" //for the charToBase function

int loadNextRead(FILE* fp, READ* read);

//PRIVATE FUNCTIONS
int readQName(FILE* fp, char* qname);
int readSeq(FILE* fp, SEQ* seq);
int readQualities(FILE* fp, READ* read);
int nextLineOfFile(FILE* fp);

#endif
