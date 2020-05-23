#ifndef LOADREF_H
#define LOADREF_H

#include <stdio.h> //for reading files

#include "../../TYPES.h"
#include "ConversionFunctions.h" //for the charToBase function

/**
 * loads the genome from a FASTA file.
 */
void loadGenome(char* filePath, GENOME* genome);

/**
 * PRIVATE FUNCTION
 * loads the info of the genome given at the beginning of the FASTA file
 */
void loadGenomeInfo(FILE* fp, char* qname);

/**
 * PRIVATE FUNCTION
 * loads the genome itself.
 */
void loadRefData(FILE* fp, REF* ref);

#endif
