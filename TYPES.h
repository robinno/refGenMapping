#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#include "PARAMS.h"

typedef uint8_t BASE;			//data type for base (A, C, G or T)
typedef uint16_t REF_INDEX;		//data type for index of the reference
typedef uint8_t SEQ_INDEX;		//data type for index of the reference
typedef uint32_t MATRIX_INDEX; 	//indexing the alignment matrix => ref_index size * seq_index size

//SEQ and REF array types
typedef struct SEQ SEQ;
struct SEQ{
	BASE* el;
	SEQ_INDEX length;
};

typedef struct REF REF;
struct REF{
	BASE* el;
	REF_INDEX length;
};

//FILE_IO types:
typedef struct FASTA_LINE FASTA_LINE;
struct FASTA_LINE{
	char Rname[buffSize];
	REF ref;
};

typedef struct FASTQ_LINE FASTQ_LINE;
struct FASTQ_LINE{
	char Qname[buffSize];
	SEQ seq;
	char qualities[seqMax];
};

typedef struct SAM_LINE SAM_LINE;
struct SAM_LINE{
	//info from FASTQ line:
	FASTQ_LINE fastQLine;

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

#endif
