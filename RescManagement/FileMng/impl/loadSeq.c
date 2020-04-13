#include "../loadSeq.h"

FILE* openFileSeqRead(){
	FILE *fp;
	fp = fopen(seqPath, "r");
	return fp;
}

int readQName(FILE* fp, char* qname){
	fgetc(fp);//skip the first @ in stream
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0){
		read = fgetc(fp);
		if((int) read == 255){//end of file
			printf("\nfile finished\n");
			return 255;
		}

		qname[i] = read;

		switch(read){
			case '\n': //end of line
				//printf("\nend of line\n");
				stoploop = 1;
				break;
			case ' ': //stop at the space
				if(nextLineOfFile(fp) == 255) return 255;
				stoploop = 1;
				break;
			default:
				i++;
				break;
		}
	}

	return 0;
}

int readSeq(FILE* fp, SEQ* seq){

	seq->el[0] = 0; //first element = 0;

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
					seq->el[i] = charToBase(read);
					printf("%c", read);
					i++;
				}
				break;
		}
	}

	seq->length = i - 1;

	return 0;
}

int readCertainties(FILE* fp, SEQ_READ* seq_input){
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0 && i < seq_input->seq.length){
		read = fgetc(fp);

		if((int) read == 255){//end of file=> would be weird
			printf("\nfile finished\n");
			return 255;
		}

		seq_input->certainties[i] = read;

		switch(read){
			case '\n': //end of line
				//printf("\nend of line\n");
				stoploop = 1;
				break;
			case ' ': //stop at the space
				if(nextLineOfFile(fp) == 255) return 255;
				stoploop = 1;
				break;
			default:
				i++;
				break;
		}
	}

	if(!(i < seq_input->seq.length)){
		if(nextLineOfFile(fp) == 255) return 255;
	}

	return 0;
}

int loadNextSeq(FILE* fp, SEQ_READ* seq_input){

	if(readQName(fp, seq_input->qname) == 255) return 255;
	if(readSeq(fp, &(seq_input->seq)) == 255) return 255;
	if(nextLineOfFile(fp) == 255) return 255;
	if(readCertainties(fp, seq_input) == 255) return 255;

	//display info on screen
	printf("length of the loaded sequence = %i\n", seq_input->seq.length);

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
