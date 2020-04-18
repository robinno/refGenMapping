#include "../align.h"

void align(FASTA_LINE fastaLine, FASTQ_LINE fastqLine, SAM_LINE* samLine,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq) {

	//left to right
//	printf("left to right alignment: \n\n");
	CELL* maxCellLR = FillInMatrix(fastaLine.ref, fastqLine.seq,
			addrSpaceMatrix);
	CELL_VALUE maxVal = maxCellLR->value;

	int retValueLR = generateCIGAR(samLine->CIGAR, maxCellLR);
	if (retValueLR == 0) {
		generateMapQ(&(samLine->MapQ), maxVal, fastqLine.seq.length);

		while (maxCellLR->prevCell != NULL)
			maxCellLR = maxCellLR->prevCell;
		samLine->Pos = maxCellLR->pos.col + 1;
		samLine->Flag = 0;

		strcpy(samLine->Rname, fastaLine.Rname);
	}

	SEQ revSeq;
	reverseSeq(fastqLine.seq, &revSeq, addrSpaceReverseSeq);

//	printf("revSeq: ");
//	for(int i = 0; i < revSeq.length; i++){
//		printf("%i", revSeq.el[i]);
//	}
//	printf("\n");
//	printf("revSeq length: %i\n", revSeq.length);

	//right to left
//	printf("right to left alignment: \n\n");
	CELL* maxCellRL = FillInMatrix(fastaLine.ref, revSeq, addrSpaceMatrix);

	int retValueRL = -1;

	if (maxCellRL->value > maxVal) {
//		printf("choosing the reverse alignment as the better one\n");
		maxVal = maxCellRL->value;
		retValueRL = generateCIGAR(samLine->CIGAR, maxCellRL);

		if (retValueRL == 0) {
			generateMapQ(&(samLine->MapQ), maxVal, fastqLine.seq.length);

			while (maxCellRL->prevCell != NULL)
				maxCellRL = maxCellRL->prevCell;
			samLine->Pos = maxCellRL->pos.col + 1;
			samLine->Flag = 16;

			strcpy(samLine->Rname, fastaLine.Rname);
		}
	}

	if(retValueLR != 0 && retValueRL != 0){
		//unmatched
		samLine->Flag = 4;
		strcpy(samLine->Rname, "*\0");
		samLine->Pos = 0;
		samLine->MapQ = 0;
		strcpy(samLine->CIGAR, "*\0");
	}

}

void reverseSeq(SEQ LeftToRight, SEQ* RightToLeft, BASE* addrSpaceReverseSeq) {
	RightToLeft->length = LeftToRight.length;
	RightToLeft->el = addrSpaceReverseSeq;

	for (SEQ_INDEX i = 0; i < LeftToRight.length; i++) {
		RightToLeft->el[i] = LeftToRight.el[LeftToRight.length - i - 1];
	}
}

int generateCIGAR(char* CIGAR, CELL* LL) {
	uint8_t cigarPartsCounter = 1;
	char ipCIGAR[buffSize];
	char ipCIGAR_temp[buffSize];

	//reset all strings
	*CIGAR = '\0';
	ipCIGAR[0] = '\0';
	ipCIGAR_temp[0] = '\0';

	SEQ_INDEX counter = 0;
	char currentDirection;

	POS prevPos = LL->prevCell->pos;
	POS currPos = LL->pos;

	if (prevPos.col == currPos.col - 1 && prevPos.row == currPos.row - 1) { //diagonal = match
		currentDirection = 'M';
	} else if (prevPos.col == currPos.col && prevPos.row == currPos.row - 1) { //up = insertion
		currentDirection = 'I';
	} else { //left = deletion
		currentDirection = 'D';
	}

	while (LL->prevCell != NULL) {
		prevPos = LL->prevCell->pos;
		currPos = LL->pos;

		if (prevPos.col == currPos.col - 1 && prevPos.row == currPos.row - 1) { //diagonal = match
			if (currentDirection == 'M') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'M';
			}
		} else if (prevPos.col == currPos.col
				&& prevPos.row == currPos.row - 1) { //up = insertion
			if (currentDirection == 'I') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'I';
			}
		} else { //left = deletion
			if (currentDirection == 'D') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDirection = 'D';
			}
		}

		LL = LL->prevCell;

//		printf("row: %i\tcol: %i\tdirection: %c\tcounter:%i\tCIGAR: %s\n",
				currPos.row, currPos.col, currentDirection, counter, ipCIGAR);
	}

	//write last counted part also in string
	sprintf(ipCIGAR_temp, "%i%c", counter, currentDirection);
	strcat(ipCIGAR_temp, ipCIGAR);
	strcpy(ipCIGAR, ipCIGAR_temp);
	ipCIGAR_temp[0] = '\0';

	strcpy(CIGAR, ipCIGAR);

	return 0;
}

void generateMapQ(uint8_t* mapQ, CELL_VALUE max_value, SEQ_INDEX seqLength) {
	//I calculate quality based on amount of similarities and gap penalties:

	//max_value is between 0 and seqLength * s => rescale between 0 and 254

	*mapQ = (uint8_t) ((((int) max_value) * 254) / (((int) seqLength) * s));
}
