#ifndef TOP_H
#define TOP_H

#include "sds_lib.h" 	//for memory free functions
#include <stdio.h> 		//for the FILE type

#include "../PARAMS.h"								//including the parameters
#include "../Alignment/smithWaterman.h" 			//for the alignment
#include "../RescManagement/MemoryMng/initMem.h"	//to initialize memory
#include "../RescManagement/FileMng/loadRef.h"		//to load the reference genome
#include "../RescManagement/FileMng/loadSeq.h"		//to load the sequences

int top();

#endif
