#ifndef PARAMS_H
#define PARAMS_H

//to make things work, defining NULL here
#define NULL ((void *)0)

//FILE PATHS
#define fastQPath "/mnt/reads.fastq"
#define samPath "/mnt/mapped.sam"
#define fastaPath "/mnt/genome.fasta"

//PARAMETERS FOR THE ALIGNMENT
#define gp 2 	//gap penalty
#define s 3		//similarity score
#define maxMutations 15 //the maximum amount of mutations in a sequence (otherwise gets thrown away)

//BUFFER SIZES
#define refMax 6000 	//maximum length of the reference genome (BUFFER SIZE)
#define seqMax 200		//maximum length of the sequence to match (BUFFER SIZE)
#define buffSize 64		//for character buffers (strings), such as qname, rname, cigar, ...

#endif
