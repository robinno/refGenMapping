#include "topheaders/free_memory.h"

void free_memory(BASE* ref){
	//free memory again
	sds_free(ref);
}
