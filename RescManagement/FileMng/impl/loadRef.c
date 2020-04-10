#include "../loadRef.h"

REF_INDEX loadRef(BASE* ref) {

	FILE* refFile = openRefFile();
	displayGenomeInfo(refFile); //also serves the purpose of skipping the first line in the genome file

	REF_INDEX refLength = loadRefData(refFile, ref);

	displayRefLoadInfo(refLength);
	closeRefFile(refFile);

	return refLength;
}

FILE* openRefFile() {
	FILE *fp;
	fp = fopen(refPath, "r");
	return fp;
}

void displayGenomeInfo(FILE* fp) { //=first line of file
	char buff[255];
	int i = 0;
	char read = ' ';
	read = fgetc(fp);
	do {
		buff[i] = read;
		i++;
		read = fgetc(fp);
	} while (read != '\n');

	while (i < 255) {
		buff[i] = '\0';
		i++;
	}

	printf("GENOME: %s\n", buff);
}

REF_INDEX loadRefData(FILE* fp, BASE* ref) {
	ref[0] = 0; //first element = 0;

	//read the file
	REF_INDEX i = 1;
	char read = fgetc(fp);
	do {
		if (charToBase(read) > 0) { //Valid base, no weird char like newline or space
			ref[i] = charToBase(read);
			i++;
		}

		//printf("%c", read); 	//debug purposes
		read = fgetc(fp); 			//move on to next char

	} while (((int) read) != 255); //end of the file

	return i - 1; //= length of ref genome
}

void displayRefLoadInfo(REF_INDEX refLength) {
	printf("\nlength of the ref = %i\n", refLength);

	if (refLength >= refMax) {
		printf("WARNING: size of buff for genome (ref) may be to small\n");
	} else {
		printf("Genome loaded successfully\n");
	}
}

void closeRefFile(FILE* fp) {
	fclose(fp);
}
