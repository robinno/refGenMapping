#include "../smithWaterman.h"

//////////////////////
//PRIVATE FUNCTIONS://

//similarity function
static inline CELL_VALUE sim(BASE a, BASE b) {
	return (a == b) ? s : -s;
}

//translating coordinates to address
static inline MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column) {
	return (((MATRIX_INDEX) row) + (MATRIX_INDEX) column * seqMax);
}

//FILL THE CURRENT CELL => core of the algorithm
static inline CELL generateCell(CELL diagonal, CELL left, CELL up, BASE refVal,
		BASE seqVal) {
	//calculate the possible  values
	CELL diagonalCELL = { diagonal.value + sim(refVal, seqVal), 1 };
	CELL leftCELL = { left.value - gp, 2 };
	CELL upCELL = { up.value - gp, 3 };
	CELL zeroCELL = { 0, 0 };

	CELL upstreamA = (leftCELL.value > upCELL.value) ? leftCELL : upCELL;
	CELL upstreamB = (diagonalCELL.value > zeroCELL.value) ? 
	diagonalCELL : zeroCELL;

	CELL newCell = (upstreamA.value > upstreamB.value) ? upstreamA : upstreamB;

	//Return the cell:
	return newCell;
}

///////////////

/////////////////////
//PUBLIC FUNCTIONS://

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

			CELL Cell = generateCell(matrix[coordToAddr(row - 1, col - 1)],
					matrix[coordToAddr(row, col - 1)],
					matrix[coordToAddr(row - 1, col)], ref.el[col - 1],
					seq.el[row - 1]);

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

