#ifndef LOADREF_H
#define LOADREF_H

#include <stdio.h> //for reading files

#include "../../PARAMS.h"
#include "functions.h" //for the charToBase function

#define refPath "/mnt/genome.fasta"

REF_INDEX loadRef(BASE* ref);

//PRIVATE FUNCTIONS:
FILE* openRefFile();
void displayGenomeInfo(FILE* fp);
REF_INDEX loadRefData(FILE* fp, BASE* ref);
void displayRefLoadInfo(REF_INDEX refLength);
void closeRefFile(FILE* fp);



#endif
