#ifndef TOP_H
#define TOP_H

#include "../RescManagement/FileMng/FASTA_interface.h"
#include "../RescManagement/FileMng/FASTQ_interface.h"
#include "../RescManagement/FileMng/SAM_interface.h"

#include "sds_lib.h" 	//for memory free functions
#include <stdio.h> 		//for the FILE type

#include "displayInfo.h"							//for feedback to the user via command line

#include "../PARAMS.h"								//including the parameters
#include "../Alignment/smithWaterman.h" 			//for the alignment
#include "../RescManagement/MemoryMng/initMem.h"	//to initialize memory

int top();

#endif
