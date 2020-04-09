#include "../../PARAMS.h"

#include "functions.h" //for the charToBase function
#include <stdio.h> //for reading files
#include "sds_lib.h" //for sds_alloc function

int initMem(BASE** seq, BASE** ref, SEQ_INDEX* seqL, REF_INDEX* refL);

SEQ_INDEX initSeq(BASE** seq);
REF_INDEX initRef(BASE** ref);


