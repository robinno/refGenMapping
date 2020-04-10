#ifndef LOADREF_H
#define LOADREF_H

#include <stdio.h> //for reading files

#include "../../PARAMS.h"
#include "functions.h" //for the charToBase function

#define refPath "/mnt/ref.txt"

int loadRef(BASE* ref, REF_INDEX refLength);

#endif
