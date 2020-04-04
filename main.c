#include "Alignment/headers/smithWaterman.h"
#include "Alignment/headers/TYPEDEFS.h"

/////////////////
// 	TEST VECTORS
#define refLength 9
#define refVector {0, 2, 4, 2, 2, 1, 3, 4, 4}

#define seqLength 10
#define seqVector {0, 4, 4, 2, 2, 4, 1, 3, 2, 1}
/////////////////

int main(int argc, char* argv[]){
	BASE seq[seqMax] = seqVector;
	BASE ref[refMax] = refVector;

	smithWaterman(ref, refLength, seq, seqLength);

	return 0;
}
