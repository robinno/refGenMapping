#include "../align.h"

void align(FASTA_LINE fastaLine, FASTQ_LINE fastqLine, SAM_LINE* samLine, CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq){

	//left to right
	//printf("left to right alignment: \n\n");
	CELL* maxCell = FillInMatrix(fastaLine.ref, fastqLine.seq, addrSpaceMatrix);
	CELL_VALUE maxVal = maxCell->value;

	generateCIGAR(samLine->CIGAR, maxCell);
	generateMapQ(&(samLine->MapQ), maxVal, fastqLine.seq.length);

	while(maxCell->prevCell != NULL)
		maxCell = maxCell->prevCell;
	samLine->Pos = maxCell->pos.col + 1;
	samLine->Flag = 0;

	SEQ revSeq;
	reverseSeq(fastqLine.seq, &revSeq, addrSpaceReverseSeq);

	//right to left
	//printf("right to left alignment: \n\n");
	maxCell = FillInMatrix(fastaLine.ref, revSeq, addrSpaceMatrix);
	if(maxCell->value > maxVal){
		printf("choosing the reverse alignment as the better one\n");
		maxVal = maxCell->value;
		generateCIGAR(samLine->CIGAR, maxCell);
		generateMapQ(&(samLine->MapQ), maxVal, fastqLine.seq.length);

		while(maxCell->prevCell != NULL)
				maxCell = maxCell->prevCell;
		samLine->Pos = maxCell->pos.col + 1;
		samLine->Flag = 16;
	}

}

void reverseSeq(SEQ LeftToRight, SEQ* RightToLeft, BASE* addrSpaceReverseSeq){
	RightToLeft->length = LeftToRight.length;
	RightToLeft->el = addrSpaceReverseSeq;

	for(SEQ_INDEX i = 0; i < LeftToRight.length; i++){
		RightToLeft->el[i] = LeftToRight.el[LeftToRight.length - i - 1];
	}
}

void generateCIGAR(char* CIGAR, CELL* LL){
	char ipCIGAR[buffSize];
	char ipCIGAR_temp[buffSize];

	ipCIGAR[0] = '\0';
	ipCIGAR_temp[0] = '\0';

	SEQ_INDEX counter = 0;
	char currentDirection;

	POS prevPos = LL->prevCell->pos;
	POS currPos = LL->pos;

	if(prevPos.col == currPos.col - 1 && prevPos.row == currPos.row - 1){//diagonal = match
		currentDirection = 'M';
	} else if(prevPos.col == currPos.col && prevPos.row == currPos.row - 1){//up = insertion
		currentDirection = 'I';
	} else {//left = deletion
		currentDirection = 'D';
	}

	while(LL->prevCell != NULL){
		prevPos = LL->prevCell->pos;
		currPos = LL->pos;

		if(prevPos.col == currPos.col - 1 && prevPos.row == currPos.row - 1){//diagonal = match
			if(currentDirection == 'M'){
				counter++;
			}else{
				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'M';
			}
		} else if(prevPos.col == currPos.col && prevPos.row == currPos.row - 1){//up = insertion
			if(currentDirection == 'I'){
				counter++;
			}else{
				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'I';
						}
		} else {//left = deletion
			if(currentDirection == 'D'){
				counter++;
			}else{
				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'D';
			}
		}

		LL = LL->prevCell;

		//printf("row: %i\tcol: %i\tdirection: %c\tcounter:%i\tCIGAR: %s\n", currPos.row, currPos.col, currentDirection, counter, CIGAR);
	}

	//write last counted part also in string
	sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
	strcat(ipCIGAR_temp, ipCIGAR);
	strcpy(ipCIGAR, ipCIGAR_temp);
	ipCIGAR_temp[0] = '\0';

	strcpy(CIGAR, ipCIGAR);
}

void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength){
	//I calculate quality based on amount of similarities and gap penalties:

	//max_value is between 0 and seqLength * s => rescale between 0 and 254

	*mapQ = (uint8_t) (( ((int)max_value) * 254 )/( ((int)seqLength) * s));
}
