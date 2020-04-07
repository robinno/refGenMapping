#include "Alignment/headers/smithWaterman.h"
#include "Alignment/headers/TYPEDEFS.h"

#include "sds_lib.h" //for sds_alloc function

/////////////////
// 	TEST VECTORS
#define refLength 9		//CHANGE WHEN FILE CHANGES! (length of file + 1)

#define seqLength 10
#define seqVector {0, 4, 4, 2, 2, 4, 1, 3, 2, 1}
/////////////////

BASE charNrBase(char c){
	if(c == 'a' || c == 'A') return 1;
	if(c == 'g' || c == 'G') return 2;
	if(c == 'c' || c == 'C') return 3;
	if(c == 't' || c == 'T') return 4;
	else return 0;
}

int main(int argc, char* argv[]){
	///////////////////////////
	//in stack memory
	BASE seq[seqMax] = seqVector;

	///////////////////////////
	//in physical memory
	BASE *ref;
	ref = (BASE *)sds_alloc(refMax * sizeof(BASE));
	if(!ref){
		sds_free(ref);
		return -1;
	}

	//init ref from file memory:
	FILE *fp;
	fp = fopen("/mnt/ref.txt", "r");
	ref[0] = 0; //first element = 0;
	for(REF_INDEX i = 1; i < refLength; i++){
		ref[i] = charNrBase(fgetc(fp));
	}
	fclose(fp);
	///////////////////////////

	//perform test
	smithWaterman(ref, refLength, seq, seqLength);

	//free memory again
	sds_free(ref);

	return 0;
}
