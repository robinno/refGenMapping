#include "../loadRef.h"

int loadRef(BASE* ref, REF_INDEX refLength) {

	//init ref from file memory:
	FILE *fp;
	fp = fopen(refPath, "r");
	ref[0] = 0; //first element = 0;
	for (REF_INDEX i = 1; i < refLength; i++) {
		ref[i] = charToBase(fgetc(fp));
	}
	fclose(fp);

}
