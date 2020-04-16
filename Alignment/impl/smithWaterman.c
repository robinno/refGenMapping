#include "../smithWaterman.h"

void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix) {
	//first row and first column of matrix = 0;
	for (SEQ_INDEX row = 0; row < seqLength; row++) {
		matrix[coordToAddr(row, 0)].value = 0;
		matrix[coordToAddr(row, 0)].pos = (POS ) { row, 0 };
		matrix[coordToAddr(row, 0)].prevCell = NULL;
	}
	for (REF_INDEX col = 0; col < refLength; col++) {
		matrix[coordToAddr(0, col)].value = 0;
		matrix[coordToAddr(0, col)].pos = (POS ) { 0, col };
		matrix[coordToAddr(0, col)].prevCell = NULL;
	}
}

CELL* FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]) {

	//FILLIN
	CELL_VALUE max = 0;
	POS maxPos; //position of the maximum value in the matrix
	for (SEQ_INDEX row = 1; row < seq.length; row++) {
		for (REF_INDEX col = 1; col < ref.length; col++) {

			CELL newCell = generateCell(
					&(matrix[coordToAddr(row - 1, col - 1)]),
					&(matrix[coordToAddr(row, col - 1)]),
					&(matrix[coordToAddr(row - 1, col)]),
					ref.el[col],
					seq.el[row],
					(POS ) { row, col });

			if (newCell.value > max) {
				maxPos = (POS ) { row, col };
				max = newCell.value;
			}

			matrix[coordToAddr(row, col)] = newCell;
		}
	}

	//////////////////
	//DEBUG PURPOSES//
	displayMatrix(ref, seq, matrix);
	displayMax(maxPos, max);
	displayLL(&(matrix[coordToAddr(maxPos.row, maxPos.col)]));
	//////////////////

	return NULL;	//&(matrix[maxPos.row][maxPos.col]);
}

char* generateCIGAR(CELL* LL){
	SEQ_INDEX counter = 0;
	char currentDirection = 'M';
	char* CIGAR;

	while(LL->prevCell != NULL){
		POS prevPos = LL->prevCell->pos;
		POS currPos = LL->pos;

		if(prevPos.col == currPos.col - 1 && prevPos.row == currPos.row - 1){//diagonal = match
			if(currentDirection == 'M'){
				counter++;
			}else{
				//write in buffer
				char newCIGAR[buffSize];
				sprintf(newCIGAR, "%i%c", counter, currentDirection);
				strcat(newCIGAR, CIGAR);
				CIGAR = newCIGAR;

				counter = 1;
				currentDirection = 'M';
			}
		} else if(prevPos.col == currPos.col && prevPos.row == currPos.row - 1){//up = insertion
			if(currentDirection == 'I'){
				counter++;
			}else{
				//write in buffer
				char newCIGAR[buffSize];
				sprintf(newCIGAR, "%i%c", counter, currentDirection);
				strcat(newCIGAR, CIGAR);
				CIGAR = newCIGAR;

				counter = 1;
				currentDirection = 'I';
						}
		} else {//left = deletion
			if(currentDirection == 'D'){
				counter++;
			}else{
				//write in buffer
				char newCIGAR[buffSize];
				sprintf(newCIGAR, "%i%c", counter, currentDirection);
				strcat(newCIGAR, CIGAR);
				CIGAR = newCIGAR;

				counter = 1;
				currentDirection = 'D';
			}
		}

		LL = LL->prevCell;
	}

	//write last counted part also in string
	char newCIGAR[buffSize];
	sprintf(newCIGAR, "%i%c", counter, currentDirection);
	strcat(newCIGAR, CIGAR);
	CIGAR = newCIGAR;

	return CIGAR;
}

//FILL THE CURRENT CELL => core of the algorithm
CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos) {

	//calculate the possible new values
	CELL_VALUE diagonalVal = diagonal->value + sim(refVal, seqVal);
	CELL_VALUE leftVal = left->value - gp;
	CELL_VALUE upVal = up->value - gp;

	//look for the maximum value:
	CELL_VALUE values[] = { 0, diagonalVal, upVal, leftVal };

	uint8_t maxIndex = 0; //Range 0-3
	for (uint8_t i = 1; i < 4; i++) {
		if (values[i] > values[maxIndex]) {
			maxIndex = i;
		}
	}

	//generate the new cell
	CELL newCell;
	newCell.pos = pos;

	switch (maxIndex) {
	case 0:
		newCell.value = 0;
		newCell.prevCell = NULL;
		break;
	case 1:
		newCell.value = diagonalVal;
		newCell.prevCell = diagonal;
		break;
	case 2:
		newCell.value = upVal;
		newCell.prevCell = up;
		break;
	case 3:
		newCell.value = leftVal;
		newCell.prevCell = left;
		break;
	}

	//Return the cell;
	return newCell;
}

//similarity function
CELL_VALUE sim(BASE a, BASE b) {
	return (a == b) ? s : -s;
}

//translating coordinates to address
MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column) {
	return (row * seqMax + column);
}
