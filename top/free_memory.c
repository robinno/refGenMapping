#include "topheaders/free_memory.h"

void free_memory(BASE* ref, CELL* addrSpaceMatrix){
	//free memory again
	sds_free(ref);
	sds_free(addrSpaceMatrix);
}
