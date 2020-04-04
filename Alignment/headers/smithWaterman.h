#ifndef SMITHWATERMAN_H
#define SMITHWATERMAN_H

#include "TYPEDEFS.h"
#include "PARAMS.h"
#include "displayForDebug.h"

CELL* smithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength);

//private functions:
CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos);
CELL_VALUE sim(BASE a, BASE b);

#endif
