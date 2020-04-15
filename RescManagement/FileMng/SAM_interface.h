#include <stdio.h>
#include <string.h>

#include "../../PARAMS.h"
#include "ConversionFunctions.h"

void initSamLine(SAM_LINE* samLine);

void displaySamLine(SAM_LINE samLine);
void writeSamLine(FILE* fp, SAM_LINE samLine);
