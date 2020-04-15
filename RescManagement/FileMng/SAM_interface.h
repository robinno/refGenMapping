#include <stdio.h>
#include <string.h>

#include "../../PARAMS.h"
#include "functions.h"

void initSamLine(SAM_LINE* samLine);

FILE* openSamFile();
void closeSamFile(FILE* fp);

void displaySamLine(SAM_LINE samLine);
void writeSamLine(FILE* fp, SAM_LINE samLine);
