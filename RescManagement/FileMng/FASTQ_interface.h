#include <stdio.h>
#include <stdlib.h>

#include "../../TYPES.h"
#include "ConversionFunctions.h" //for the charToBase function

int readNextFastqLine(FILE* fp, FASTQ_LINE* fastQLine);

//PRIVATE FUNCTIONS
int readQName(FILE* fp, char* qname);
int readSeq(FILE* fp, SEQ* seq);
int readQualities(FILE* fp, FASTQ_LINE* fastQLine);
int nextLineOfFile(FILE* fp);
