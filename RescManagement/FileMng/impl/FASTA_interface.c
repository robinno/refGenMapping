#include "../FASTA_interface.h"

void loadRef(char* filePath, FASTA_LINE* fastaLine) {

	FILE* refFile = fopen(filePath, "r");

	loadGenomeInfo(refFile, fastaLine->Rname);
	loadRefData(refFile, &(fastaLine->ref));

	fclose(refFile);
}

void loadGenomeInfo(FILE* fp, char* qname) { //=first line of file
	fgetc(fp);//skip the first @ in stream
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0){
		read = fgetc(fp);

		if(read == ' ' || read == '\n'){
			while(read != '\n'){ //Get to next line of stream if it was a space
				read = fgetc(fp);
			}
			qname[i] = '\0';
			return;
		}else{
			qname[i] = read;
			i++;
		}
	}
}

void loadRefData(FILE* fp, REF* ref) {
	ref->el[0] = 0; //first element = 0;

	//read the file
	ref->length = 1;
	char read = fgetc(fp);
	do {
		if (charToBase(read) > 0) { //Valid base, no weird char like newline or space
			ref->el[ref->length] = charToBase(read);
			ref->length++;
		}
		read = fgetc(fp); 			//move on to next char
	} while (((int) read) != 255); //end of the file
}

