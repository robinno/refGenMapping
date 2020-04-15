#ifndef INITMEM_H
#define INITMEM_H

#include "../../PARAMS.h"
#include "../../TYPES.h"

#include "sds_lib.h" //for sds_alloc function

int initSeq(BASE** seq);
int initRef(BASE** ref);
int initAlignMatrixAddrSpace(CELL** matrix);

#endif
