#include "../align.h"

//////////////////////
//PRIVATE FUNCTIONS://


//translating coordinates to address
static inline MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column) {
	return (((MATRIX_INDEX) row) + (MATRIX_INDEX) column * seqMax);
}


static inline POS goToDirection(CELL* matrix, POS pos) {
	switch (matrix[coordToAddr(pos.row, pos.col)].d) {
	case 1:
		return (POS ) { pos.row - 1, pos.col - 1 } ;
		break;
	case 2:
		return (POS ) { pos.row, pos.col - 1 } ;
		break;
	case 3:
		return (POS ) { pos.row - 1, pos.col } ;
		break;
	default:
		printf("something went wrong when backtracking");
		return (POS ) { 0, 0 } ;
		break;
	}
}



int generateCIGAR(char* CIGAR, CELL* matrix, POS maxPos) {
	uint8_t cigarPartsCounter = 1;
	char ipCIGAR[buffSize];
	char ipCIGAR_temp[buffSize];

	//reset all strings
	*CIGAR = '\0';
	ipCIGAR[0] = '\0';
	ipCIGAR_temp[0] = '\0';

	SEQ_INDEX counter = 0;
	char currentDir = '\0';

	POS pos = maxPos;
	DIRECTION d = matrix[coordToAddr(pos.row, pos.col)].d;

	switch (d) {
	case 1: //diagonal: match
		currentDir = 'M';
		break;
	case 2: //up : insertion
		currentDir = 'I';
		break;
	case 3: //left: deletion
		currentDir = 'D';
		break;
	}

	while (d != 0) {
		switch (d) {
		case 1:
			if (currentDir == 'M') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDir);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDir = 'M';
			}
			pos = (POS ) { pos.row - 1, pos.col - 1 };
			break;
		case 2:
			if (currentDir == 'I') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDir);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDir = 'I';
			}
			pos = (POS ) { pos.row, pos.col - 1 };
			break;
		case 3:
			if (currentDir == 'D') {
				counter++;
			} else {
				cigarPartsCounter++;
				if (cigarPartsCounter >= maxCigarParts)
					return -1;

				sprintf(ipCIGAR_temp, "%i%c", counter, currentDir);
				strcat(ipCIGAR_temp, ipCIGAR);
				strcpy(ipCIGAR, ipCIGAR_temp);
				ipCIGAR_temp[0] = '\0';

				counter = 1;
				currentDir = 'D';
			}
			pos = (POS ) { pos.row - 1, pos.col };
			break;
		}
//		printf("row: %i\tcol: %i\tdirection: %c\tcounter:%i\tCIGAR: %s\n",
//				currPos.row, currPos.col, currentDirection, counter, ipCIGAR);

		d = matrix[coordToAddr(pos.row, pos.col)].d;
	}

	//write last counted part also in string
	sprintf(ipCIGAR_temp, "%i%c", counter, currentDir);
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
			RightToLeft->seq.el[i] = A;
			break;
		}
	}
}

///////////////

/////////////////////
//PUBLIC FUNCTIONS://

void align(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead) {

	mapped_read->read = *read;
	CELL* matrix = addrSpaceMatrix;

	//left to right
	//	printf("left to right alignment: \n\n");
	POS maxPosLR = FillInMatrix(genome.ref, read->seq, matrix);
	CELL_VALUE maxVal = matrix[coordToAddr(maxPosLR.row, maxPosLR.col)].value;

	int retValueLR = generateCIGAR(mapped_read->CIGAR, matrix, maxPosLR);
	if (retValueLR == 0) {
		generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

		POS pos = goToDirection(matrix, maxPosLR);
		while (matrix[coordToAddr(pos.row, pos.col)].value != 0) {
			pos = goToDirection(matrix, pos);
		}

		mapped_read->Pos = pos.col + 1;
		mapped_read->Flag = 0;

		strcpy(mapped_read->Rname, genome.Rname);
	}

	reverseSeq(*read, revRead, addrSpaceReverseSeq);

	POS maxPosRL = FillInMatrix(genome.ref, revRead->seq, matrix);

	int retValueRL = -1;

	if (matrix[coordToAddr(maxPosRL.row, maxPosRL.col)].value > maxVal) {
//		printf("choosing the reverse alignment as the better one\n");
		maxVal = matrix[coordToAddr(maxPosRL.row, maxPosRL.col)].value;
		retValueRL = generateCIGAR(mapped_read->CIGAR, matrix, maxPosRL);

		if (retValueRL == 0) {
			generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

			POS pos = goToDirection(matrix, maxPosRL);
			while (matrix[coordToAddr(pos.row, pos.col)].value != 0) {
				pos = goToDirection(matrix, pos);
			}

			mapped_read->Pos = pos.col + 1;
			mapped_read->Flag = 16;

			strcpy(mapped_read->Rname, genome.Rname);

			//use reverse read
			mapped_read->read = *revRead;
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
}

void alignHW(GENOME genome, READ* read, MAPPED_READ* mapped_read,
		CELL* addrSpaceMatrix, BASE* addrSpaceReverseSeq, READ* revRead) {

	mapped_read->read = *read;
	CELL* matrix = addrSpaceMatrix;

	//left to right
	//	printf("left to right alignment: \n\n");
	MATRIX_INDEX addr = FillInHW(genome.ref.el,genome.ref.length, read->seq.el,read->seq.length, matrix);
	POS maxPosLR = {addr % seqMax, addr / seqMax};

	CELL_VALUE maxVal = matrix[coordToAddr(maxPosLR.row, maxPosLR.col)].value;

	int retValueLR = generateCIGAR(mapped_read->CIGAR, matrix, maxPosLR);
	if (retValueLR == 0) {
		generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

		POS pos = goToDirection(matrix, maxPosLR);
		while (matrix[coordToAddr(pos.row, pos.col)].value != 0) {
			pos = goToDirection(matrix, pos);
		}

		mapped_read->Pos = pos.col + 1;
		mapped_read->Flag = 0;

		strcpy(mapped_read->Rname, genome.Rname);
	}

	reverseSeq(*read, revRead, addrSpaceReverseSeq);

	addr = FillInHW(genome.ref.el, genome.ref.length, revRead->seq.el,revRead->seq.length, matrix);
	POS maxPosRL = {addr % seqMax, addr / seqMax};

	int retValueRL = -1;

	if (matrix[coordToAddr(maxPosRL.row, maxPosRL.col)].value > maxVal) {
//		printf("choosing the reverse alignment as the better one\n");
		maxVal = matrix[coordToAddr(maxPosRL.row, maxPosRL.col)].value;
		retValueRL = generateCIGAR(mapped_read->CIGAR, matrix, maxPosRL);

		if (retValueRL == 0) {
			generateMapQ(&(mapped_read->MapQ), maxVal, read->seq.length);

			POS pos = goToDirection(matrix, maxPosRL);
			while (matrix[coordToAddr(pos.row, pos.col)].value != 0) {
				pos = goToDirection(matrix, pos);
			}

			mapped_read->Pos = pos.col + 1;
			mapped_read->Flag = 16;

			strcpy(mapped_read->Rname, genome.Rname);

			//use reverse read
			mapped_read->read = *revRead;
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
}


