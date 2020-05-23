#ifndef FASTQ_INF_H
#define FASTQ_INF_H

#include <stdio.h>
#include <stdlib.h>

#include "../../TYPES.h"
#include "ConversionFunctions.h" //for the charToBase function

/**
 * Loads the next read from the FASTQ file stream
 * and stores it in the read type given.
 * (fp = file pointer)
 */
int loadNextRead(FILE* fp, READ* read);

/**
 * PRIVATE FUNCTION:
 * reads the Qname from the FASTQ file,
 * given we start at the right position in the stream.
 */
int readQName(FILE* fp, char* qname);

/**
 * PRIVATE FUNCTION:
 * reads the sequence from the FASTQ file,
 *  given we start at the right position in the stream.
 */
int readSeq(FILE* fp, SEQ* seq);

/**
 * PRIVATE FUNCTION:
 * reads the qualities from the FASTQ file,
 * given we start at the right position in the stream.
 */
int readQualities(FILE* fp, READ* read);

/**
 * PRIVATE FUNCTION:
 * skips the stream until the next line break (newline) in the file
 */
int nextLineOfFile(FILE* fp);

#endif
