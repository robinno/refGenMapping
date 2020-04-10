#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

//PARAMETERS FOR THE ALIGNMENT
#define gp 2 	//gap penalty
#define s 3		//similarity score

//BUFFER SIZES
#define refMax 15 		//maximum length of the reference genome (BUFFER SIZE)
#define seqMax 15		//maximum length of the sequence to match (BUFFER SIZE)

//TYPEDEFS
typedef uint8_t BASE;		//data type for base (A, C, G or T)
typedef uint8_t REF_INDEX;	//data type for index of the reference
typedef uint8_t SEQ_INDEX;	//data type for index of the reference

typedef uint8_t MATRIX_INDEX; //indexing the alignment matrix => ref_index size * seq_index size

///////////////////////////////////////////////////////////////////////////////////////////
//TYPEDEFS WITHIN ALIGNMENT
typedef int CELL_VALUE;		//data type for values during the alignment
typedef struct POS POS;	//data type to keep track of position in alignment matrix
struct POS {
	SEQ_INDEX row;
	REF_INDEX col;
};
typedef struct CELL CELL;//data type of a specific cell in the alignment matrix
struct CELL {
	CELL_VALUE value;
	POS pos;
	CELL* prevCell;
};

//to make it work, defining NULL
#define NULL ((void *)0)

#endif
