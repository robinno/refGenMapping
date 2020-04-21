#ifndef SAM_INF_H
#define SAM_INF_H

#include <stdio.h>
#include <string.h>

#include "../../PARAMS.h"
#include "ConversionFunctions.h"

void initMappedRead(MAPPED_READ* mapped_read);
void writeSamLine(FILE* fp, MAPPED_READ mapped_read);

#endif
