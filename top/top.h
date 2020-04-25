#ifndef TOP_H
#define TOP_H

#include "sds_lib.h" 	//for memory free functions
#include <stdio.h> 		//for the FILE type
#include <inttypes.h> 	//to print weird types, like 64 bit integers

#include "../PARAMS.h"								//including the parameters
#include "../TYPES.h"								//including the types

#include "../RescManagement/FileMng/FASTA_interface.h"
#include "../RescManagement/FileMng/FASTQ_interface.h"
#include "../RescManagement/FileMng/SAM_interface.h"
#include "../RescManagement/MemoryMng/initMem.h"	//to initialize memory

#include "../Alignment/smithWaterman.h" 			//for the alignment
#include "../Alignment/align.h"


#include "displayInfo.h"							//for feedback to the user via command line
#include "Perf_counter.h"

int top();

#endif
