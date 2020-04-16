#include "../FASTQ_interface.h"

int readNextFastqLine(FILE* fp, FASTQ_LINE* fastQLine){

	if(readQName(fp, fastQLine->Qname) == 255) return 255;
	if(readSeq(fp, &(fastQLine->seq)) == 255) return 255;
	if(nextLineOfFile(fp) == 255) return 255;
	if(readQualities(fp, fastQLine) == 255) return 255;

	//display info on screen
	//printf("length of the loaded sequence = %i\n", fastQLine->seq.length);

	return 0;
}

int readQName(FILE* fp, char* qname){
	fgetc(fp);//skip the first @ in stream
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0){
		read = fgetc(fp);
		if((int) read == 255){//end of file
			//printf("\nfile finished\n");
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

		if(stoploop == 1)
			qname[i] = '\0';
	}

	return 0;
}

int readSeq(FILE* fp, SEQ* seq){
	//Read the sequence
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0){
		read = fgetc(fp);

		if((int) read == 255){//end of file
			//printf("\nfile finished\n");
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
					//printf("%c", read);
					i++;
				}
				break;
		}
	}

	seq->length = i - 1;

	return 0;
}

int readQualities(FILE* fp, FASTQ_LINE* fastQLine){
	int i = 0;
	char read;
	int stoploop = 0;
	while(stoploop == 0 && i < fastQLine->seq.length){
		read = fgetc(fp);

		if((int) read == 255){//end of file
			//printf("\nfile finished\n");
			return 255;
		}

		if(read == ' ')
			read = '\0';

		fastQLine->qualities[i] = read;

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

	if(!(i < fastQLine->seq.length)){
		if(nextLineOfFile(fp) == 255) return 255;
	}

	return 0;
}

int nextLineOfFile(FILE* fp){
	char read = fgetc(fp);

	while(read != '\n'){
		if((int) read == 255){
			//printf("file finished\n");
			return 255;
		}

		read = fgetc(fp);
	}

	return 0;
}
