#ifndef PARAMS_H
#define PARAMS_H

//to make things work, defining NULL here
#define NULL ((void *)0)

//FILE PATHS
#define fastQPath "/mnt/reads.fastq"
#define samPathSW "/mnt/mappedSW.sam"
#define samPathHW "/mnt/mappedHW.sam"
#define fastaPath "/mnt/genome.fasta"

//PARAMETERS FOR THE ALIGNMENT
#define gp 2 	//gap penalty
#define s 3		//similarity score
#define maxCigarParts 15 //the maximum amount of parts in the CIGAR (otherwise sequence marked as unmatched)

//BUFFER SIZES
#define refMax 5700 	//maximum length of the reference genome (BUFFER SIZE)
#define seqMax 160		//maximum length of the sequence to match (BUFFER SIZE)
#define buffSize 64		//for character buffers (strings), such as qname, rname, cigar, ...

//define the bases:
#define A 0b00
#define C 0b01
#define G 0b10
#define T 0b11

#endif
