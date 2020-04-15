#ifndef LOADREF_H
#define LOADREF_H

#include <stdio.h> //for reading files

#include "../../PARAMS.h"
#include "functions.h" //for the charToBase function

REF_INDEX loadRef(BASE* ref);

//PRIVATE FUNCTIONS:
FILE* openFASTQFile();
void displayGenomeInfo(FILE* fp);
REF_INDEX loadRefData(FILE* fp, BASE* ref);
void displayRefLoadInfo(REF_INDEX refLength);
void closeFASTQFile(FILE* fp);



#endif
