#include "../loadSeq.h"

FILE* openFileSeqRead(){
	FILE *fp;
	fp = fopen(seqPath, "r");
	fgetc(fp);//skip the first @ in stream
	return fp;
}

int loadNextSeq(FILE* fp, BASE* seq, SEQ_INDEX* seqLength){
	printf("loading read ...\n");

	//skip first line
	nextLineOfFile(fp);

	seq[0] = 0; //first element = 0;

	//Read the sequence
	int i = 1;
	char read;
	int stoploop = 0;
	while(stoploop == 0){
		read = fgetc(fp);

		if((int) read == 255){//end of file
			printf("\nfile finished\n");
			return 255;
		}

		switch(read){
			case '\n': //end of line
				//printf("\nend of line\n");
				stoploop = 1;
				break;
			case 'n': //uncertain bases, trunc the read till here:
			case 'N':
				if(nextLineOfFile(fp) == 255) return 255;
				stoploop = 1;
				break;
			default:
				if(charToBase(read) > 0){ //valid base
					seq[i] = charToBase(read);
					printf("%c", read);
					i++;
				}
				break;
		}
	}

	//skip 2 lines => I dont care about the other stuff and things in the file
	if(nextLineOfFile(fp) == 255) return 255;
	if(nextLineOfFile(fp) == 255) return 255;

	*seqLength = i - 1;

	//display info on screen
	printf("length of the loaded sequence = %i\n", *seqLength);

	return 0;
}

void closeFileSeqRead(FILE* fp){
	//close file again
	fclose(fp);
}

int nextLineOfFile(FILE* fp){
	char read = fgetc(fp);

	while(read != '\n'){
		if((int) read == 255){
			printf("file finished\n");
			return 255;
		}

		read = fgetc(fp);
	}

	return 0;
}
