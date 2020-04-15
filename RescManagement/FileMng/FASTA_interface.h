#ifndef LOADREF_H
#define LOADREF_H

#include <stdio.h> //for reading files

#include "../../TYPES.h"
#include "ConversionFunctions.h" //for the charToBase function


void loadRef(char* filePath, FASTA_LINE* fastaLine);

//private functions
void loadGenomeInfo(FILE* fp, char* qname);
void loadRefData(FILE* fp, REF* ref);


#endif
