#include "../smithWaterman.h"

void initMatrix(REF_INDEX refLength, SEQ_INDEX seqLength, CELL* matrix) {
	//first row and first column of matrix = 0;
	for (SEQ_INDEX row = 0; row < seqLength; row++) {
		matrix[coordToAddr(row, 0)].value = 0;
		matrix[coordToAddr(row, 0)].d = 0;
	}
	for (REF_INDEX col = 0; col < refLength; col++) {
		matrix[coordToAddr(0, col)].value = 0;
		matrix[coordToAddr(0, col)].d = 0;
	}
}

POS FillInMatrix(REF ref, SEQ seq, CELL matrix[refMax * seqMax]) {
	CELL_VALUE max = 0;
	POS maxPos = { 0, 0 }; //position of the maximum value in the matrix

	for (SEQ_INDEX row = 1; row <= seq.length; row++) {
		for (REF_INDEX col = 1; col <= ref.length; col++) {

			CELL Cell = generateCell(
					&(matrix[coordToAddr(row - 1, col - 1)]),
					&(matrix[coordToAddr(row, col - 1)]),
					&(matrix[coordToAddr(row - 1, col)]), ref.el[col - 1],
					seq.el[row - 1], (POS ) { row, col });

			if (Cell.value > max) {
				maxPos = (POS ) { row, col };
				max = Cell.value;
			}

			matrix[coordToAddr(row, col)] = Cell;
		}
	}

	//////////////////
	//DEBUG PURPOSES//
//	displayMatrix(ref, seq, matrix);
//	displayMax(maxPos, max);
	//displayLL(&(matrix[coordToAddr(maxPos.row, maxPos.col)]));
	//////////////////

	return maxPos;
}

//FILL THE CURRENT CELL => core of the algorithm
CELL generateCell(CELL* diagonal, CELL* left, CELL* up, BASE refVal,
		BASE seqVal, POS pos) {

	//calculate the possible  values
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

	switch (maxIndex) {
	case 0:
		newCell.value = 0;
		newCell.d = 0;
		break;
	case 1:
		newCell.value = diagonalVal;
		newCell.d = 1;
		break;
	case 2:
		newCell.value = upVal;
		newCell.d = 2;
		break;
	case 3:
		newCell.value = leftVal;
		newCell.d = 3;
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
	return (((MATRIX_INDEX) row) * refMax + (MATRIX_INDEX) column);
}
