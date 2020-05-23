#ifndef SAM_INF_H
#define SAM_INF_H

#include <stdio.h>
#include <string.h>

#include "../../PARAMS.h"
#include "ConversionFunctions.h"

/**
 * Initializes the mapped_read type with the defaults for this implementation:
 * Rnext, Pnext and Tlen all set to 0.
 */
void initMappedRead(MAPPED_READ* mapped_read);

/**
 * Writes the mapped_read type to the given file (fp = file pointer)
 */
void writeSamLine(FILE* fp, MAPPED_READ mapped_read);

#endif
