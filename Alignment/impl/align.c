#include "../align.h"

READ* align(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead) {

	READ* returnRead = read;

	//left to right
//	printf("left to right alignment: \n\n");
	CELL* maxCellLR = FillInMatrix(genome.ref, read->seq, addrSpaceMatrix);
	CELL_VALUE maxVal = maxCellLR->value;

	int retValueLR = generateCIGAR(mapped_read->CIGAR, maxCellLR);
	if (retValueLR == 0) {
		generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

		while (maxCellLR->prevCell != NULL)
			maxCellLR = maxCellLR->prevCell;
		mapped_read->Pos = maxCellLR->pos.col + 1;
		mapped_read->Flag = 0;

		strcpy(mapped_read->Rname, genome.Rname);
	}

	reverseSeq(*read, revRead, addrSpaceReverseSeq);

	CELL* maxCellRL = FillInMatrix(genome.ref, revRead->seq, addrSpaceMatrix);

	int retValueRL = -1;

	if (maxCellRL->value > maxVal) {
//		printf("choosing the reverse alignment as the better one\n");
		maxVal = maxCellRL->value;
		retValueRL = generateCIGAR(mapped_read->CIGAR, maxCellRL);

		if (retValueRL == 0) {
			generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

			while (maxCellRL->prevCell != NULL)
				maxCellRL = maxCellRL->prevCell;
			mapped_read->Pos = maxCellRL->pos.col + 1;
			mapped_read->Flag = 16;

			strcpy(mapped_read->Rname, genome.Rname);

			//use reverse read
			returnRead = revRead;
		}
	}

	if (retValueLR != 0 && retValueRL != 0) {
		//unmatched
		mapped_read->Flag = 4;
		strcpy(mapped_read->Rname, "*\0");
		mapped_read->Pos = 0;
		mapped_read->MapQ = 0;
		strcpy(mapped_read->CIGAR, "*\0");
	}

	return returnRead;
}

void reverseSeq(READ LeftToRight, READ* RightToLeft, BASE* addrSpaceReverseSeq) {
	strcpy(RightToLeft->Qname, LeftToRight.Qname);

	RightToLeft->seq.length = LeftToRight.seq.length;
	RightToLeft->seq.el = addrSpaceReverseSeq;

	//reverse AND complementary base

	for (SEQ_INDEX i = 0; i < LeftToRight.seq.length; i++) {
		RightToLeft->qualities[i] = LeftToRight.qualities[LeftToRight.seq.length
				- i - 1];
		BASE b = LeftToRight.seq.el[LeftToRight.seq.length - i - 1];
		switch (b) {
		case A:
			RightToLeft->seq.el[i] = T;
			break;
		case C:
			RightToLeft->seq.el[i] = G;
			break;
		case G:
			RightToLeft->seq.el[i] = C;
			break;
		case T:
			RightToLeft->seq.el[i] = T;
			break;
		}
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
//				currPos.row, currPos.col, currentDirection, counter, ipCIGAR);
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
