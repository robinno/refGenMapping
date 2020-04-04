#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>

typedef uint8_t BASE;
typedef uint8_t REF_INDEX;
typedef uint8_t SEQ_INDEX;
typedef int CELL_VALUE;

typedef struct POS POS;
struct POS {
	SEQ_INDEX row;
	REF_INDEX col;
};

typedef struct CELL CELL;
struct CELL {
	CELL_VALUE value;
	POS pos;
	CELL* prevCell;
};

//to make it work, defining NULL
#define NULL ((void *)0)

#endif
