#include "headers/smithWaterman.h"

CELL* smithWaterman(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength) {

	//INIT MATRIX
	CELL matrix[seqMax][refMax];

	//first row and first column = 0;
	for (SEQ_INDEX row = 0; row < seqLength; row++) {
		matrix[row][0].value = 0;
		matrix[row][0].pos = (POS ) { 0, 0 };
		matrix[row][0].prevCell = NULL;
	}
	for (REF_INDEX col = 0; col < refLength; col++) {
		matrix[0][col].value = 0;
		matrix[0][col].pos = (POS ) { 0, 0 };
		matrix[0][col].prevCell = NULL;
	}

	//FILLIN
	CELL_VALUE max = 0;
	POS maxPos; //position of the maximum value in the matrix
	for (SEQ_INDEX row = 1; row < seqLength; row++) {
		for (REF_INDEX col = 1; col < refLength; col++) {
			BASE refVal = ref[col];
			BASE seqVal = seq[row];
			CELL newCell = generateCell(&(matrix[row - 1][col - 1]),
					&(matrix[row][col - 1]), &(matrix[row - 1][col]), refVal,
					seqVal, (POS ) { row, col });
			if (newCell.value > max) {
				maxPos = (POS ) { row, col };
				max = newCell.value;
			}
			matrix[row][col] = newCell;
		}
	}

	//////////////////
	//DEBUG PURPOSES//
	displayMatrix(ref, refLength, seq, seqLength, matrix);
	displayMax(maxPos, max);
	displayLL(&(matrix[maxPos.row][maxPos.col]));
	//////////////////

	return &(matrix[maxPos.row][maxPos.col]);
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
