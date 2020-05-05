#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#include "PARAMS.h"

typedef uint8_t BASE;			//data type for base (A, C, G or T)
typedef uint16_t REF_INDEX;		//data type for index of the reference
typedef uint16_t SEQ_INDEX;		//data type for index of the reference
typedef uint32_t MATRIX_INDEX; //indexing the alignment matrix => ref_index size * seq_index size

//SEQ and REF array types
typedef struct SEQ SEQ;
struct SEQ {
	BASE* el;
	SEQ_INDEX length;
};

typedef struct REF REF;
struct REF {
	BASE* el;
	REF_INDEX length;
};

//FILE_IO types:
typedef struct GENOME GENOME;
struct GENOME {
	char Rname[buffSize];
	REF ref;
};

typedef struct READ READ;
struct READ {
	char Qname[buffSize];
	SEQ seq;
	char qualities[seqMax];
};

typedef struct MAPPED_READ MAPPED_READ;
struct MAPPED_READ {
	//info from FASTQ line:
	READ read;

	//info from FASTA line
	char Rname[buffSize];

	//mapping results
	uint16_t Flag;
	REF_INDEX Pos;
	uint8_t MapQ;
	char CIGAR[buffSize];

	//defaults:
	char Rnext[1];			// = {'*'};
	REF_INDEX Pnext;		// = 0;
	REF_INDEX Tlen;			// = 0;
};

//TYPES USED WITHIN ALIGNMENT
typedef struct POS POS;	//data type to keep track of position in alignment matrix
struct POS {
	SEQ_INDEX row;
	REF_INDEX col;
};


typedef uint16_t DIRECTION;
typedef int16_t CELL_VALUE;		//data type for values during the alignment

typedef struct CELL CELL;//data type of a specific cell in the alignment matrix
struct CELL {
	CELL_VALUE value;
	DIRECTION d;
};

#endif
