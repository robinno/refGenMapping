#include "../smithWaterman.h"

void initSmithWaterman(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix) {
	//first row and first column of matrix = 0;
	for (SEQ_INDEX row = 0; row < seqLength; row++) {
		matrix[coordToAddr(row, 0)].value = 0;
		matrix[coordToAddr(row, 0)].pos = (POS ) { 0, 0 };
		matrix[coordToAddr(row, 0)].prevCell = NULL;
	}
	for (REF_INDEX col = 0; col < refLength; col++) {
		matrix[coordToAddr(0, col)].value = 0;
		matrix[coordToAddr(0, col)].pos = (POS ) { 0, 0 };
		matrix[coordToAddr(0, col)].prevCell = NULL;
	}
}

CELL* smithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]) {

	//FILLIN
	CELL_VALUE max = 0;
	POS maxPos; //position of the maximum value in the matrix
	for (SEQ_INDEX row = 1; row < seqLength; row++) {
		for (REF_INDEX col = 1; col < refLength; col++) {

			CELL newCell = generateCell(
					&(matrix[coordToAddr(row - 1, col - 1)]),
					&(matrix[coordToAddr(row, col - 1)]),
					&(matrix[coordToAddr(row - 1, col)]), ref[col], seq[row],
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
	displayMatrix(ref, refLength, seq, seqLength, matrix);
	displayMax(maxPos, max);
	displayLL(&(matrix[coordToAddr(maxPos.row, maxPos.col)]));
	//////////////////

	return NULL;	//&(matrix[maxPos.row][maxPos.col]);
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