#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

//FILE PATHS
#define fastQPath "/mnt/reads.fastq"
#define samPath "/mnt/mapped.sam"
#define fastaPath "/mnt/genome.fasta"

//PARAMETERS FOR THE ALIGNMENT
#define gp 2 	//gap penalty
#define s 3		//similarity score

//BUFFER SIZES
#define refMax 6000 		//maximum length of the reference genome (BUFFER SIZE)
#define seqMax 150		//maximum length of the sequence to match (BUFFER SIZE)

//TYPEDEFS
typedef uint8_t BASE;		//data type for base (A, C, G or T)
typedef uint16_t REF_INDEX;	//data type for index of the reference
typedef uint8_t SEQ_INDEX;	//data type for index of the reference

typedef uint16_t MATRIX_INDEX; //indexing the alignment matrix => ref_index size * seq_index size

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


//FILES:
typedef struct FASTA_LINE FASTA_LINE;
struct FASTA_LINE{
	char Rname[buffSize];
	REF ref;
};

typedef struct FASTQ_LINE FASTQ_LINE;
struct FASTQ_LINE{
	char Qname[255];
	SEQ seq;
	char qualities[seqMax];
};

typedef struct SAM_LINE SAM_LINE;
struct SAM_LINE{
	//info from FASTQ line:
	FASTQ_LINE fastQLine;

	//info from FASTA line
	FASTA_LINE fastALine;

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

///////////////////////////////////////////////////////////////////////////////////////////
//to make it work, defining NULL
#define NULL ((void *)0)

#endif
