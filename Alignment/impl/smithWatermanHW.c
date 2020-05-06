#include "../smithWatermanHW.h"

/////////////////////
//PUBLIC FUNCTIONS://

static inline CELL generateCellHW(BASE refVal, BASE seqVal,
		CELL_VALUE diagonalVal, CELL_VALUE leftVal, CELL_VALUE upval){
	CELL_VALUE sim = (refVal == seqVal) ? s : -s;

	//calculate the possible  values
	CELL diagonalCELL = { diagonalVal + sim, 1 };
	CELL leftCELL = { leftVal - gp, 2 };
	CELL upCELL = { upval - gp, 3 };
	CELL zeroCELL = { 0, 0 };

	CELL upstreamA = (leftCELL.value > upCELL.value) ? leftCELL : upCELL;
	CELL upstreamB =
			(diagonalCELL.value > zeroCELL.value) ? diagonalCELL : zeroCELL;

	CELL Cell = (upstreamA.value > upstreamB.value) ? upstreamA : upstreamB;

	return Cell;
}

POS FillInHW2(REF ref, SEQ seq, CELL matrix[refMax * seqMax]) {

	//maximum value searching:
	CELL_VALUE currentMaxVal = 0;
	POS maxPos = { 0, 0 };

	//diagonal registers:
	CELL_VALUE currDiagonal[seqMax];
	CELL_VALUE prevDiagonal[seqMax];
	CELL_VALUE prevprevDiagonal[seqMax];

	//init:
	prevprevDiagonal[0] = 0;
	prevDiagonal[0] = 0;
	prevDiagonal[1] = 0;
	currDiagonal[0] = 0;

	//start at second column:
	for (REF_INDEX currCol = 2; currCol < refMax + seqMax; currCol++) {

		//Edge case
		if (currCol > ref.length + seq.length)
			break;

		//new diagonal generation loop
		for (SEQ_INDEX i = 1; i < seqMax; i++) {
			SEQ_INDEX row = i;
			REF_INDEX col = currCol - i;

			//Edge cases
			if (i >= seq.length)
				break;
			if (col == 0)
				break;
			if (col >= ref.length)
				continue; //still has to do the rest of the loops, since col will decrease.

			//Generation
			CELL cell = generateCellHW(ref.el[col - 1], seq.el[row - 1],
					prevprevDiagonal[i - 1], prevDiagonal[i],
					prevDiagonal[i - 1]);

			//storing
			currDiagonal[i] = cell.value;
			matrix[row + col * seqMax] = cell;

			//maximum value search:
			if (cell.value > currentMaxVal) {
				maxPos = (POS ) { row, col};
				currentMaxVal = cell.value;
			}
		}

		//shift values:
		for (SEQ_INDEX j = 0; j < seqMax; j++) {
			prevprevDiagonal[j] = prevDiagonal[j];
			prevDiagonal[j] = currDiagonal[j];
		}
	}

	return maxPos;
}

void FIMHW(BASE ref[sliceSize], BASE seq[seqMax], MATRIX_INDEX seqLength,
		CELL matrix[sliceSize * seqMax], POS* maxPos, CELL_VALUE* currentMaxVal, REF_INDEX coloffset) {
	CELL localMatrix[sliceSize * seqMax];
//#pragma HLS data_pack variable=matrix
//#pragma HLS data_pack variable=maxPos
//
//#pragma HLS PIPELINE

	MATRIX_INDEX col, row;

//#pragma HLS loop_merge

//first row is zero:
	for (col = 0; col < sliceSize; col++) {
		//#pragma HLS PIPELINE
		localMatrix[col * seqMax] = (CELL ) { 0, 0 };
	}

	//first column is last column of previous slice
	for (row = 1; row < seqMax; row++) {
		//#pragma HLS PIPELINE
		localMatrix[row] = matrix[row];
	}

	//the fillin
	COL: for (col = 1; col < sliceSize; col++) {
		ROW: for (row = 1; row < seqLength/*seqMax*/; row++) {
//#pragma HLS loop_tripcount min=75 max=300 avg=150

			//#pragma HLS UNROLL
			CELL_VALUE sim = (ref[col - 1] == seq[row - 1]) ? s : -s;

			//calculate the possible  values
			CELL diagonalCELL = {
					localMatrix[(row - 1) + (col - 1) * seqMax].value + sim, 1 };
			CELL leftCELL = {
					localMatrix[(row) + (col - 1) * seqMax].value - gp, 2 };
			CELL upCELL = { localMatrix[(row - 1) + (col) * seqMax].value - gp,
					3 };
			CELL zeroCELL = { 0, 0 };

			CELL upstreamA =
					(leftCELL.value > upCELL.value) ? leftCELL : upCELL;
			CELL upstreamB =
					(diagonalCELL.value > zeroCELL.value) ?
							diagonalCELL : zeroCELL;

			CELL Cell =
					(upstreamA.value > upstreamB.value) ? upstreamA : upstreamB;

			if (Cell.value > *currentMaxVal) {
				*maxPos = (POS ) { row, col + coloffset};
				*currentMaxVal = Cell.value;
			}

			localMatrix[row + col * seqMax] = Cell; //assign in local matrix
			matrix[row + col * seqMax] = Cell;		//assign in global matrix
		}
	}
}

POS FillInMatrixHW(REF ref, SEQ seq, CELL matrix[refMax * seqMax]) {
	CELL_VALUE currentMaxVal = 0;
	POS maxPos = { 0, 0 };

	REF_INDEX refPointerOffset = 0;
	MATRIX_INDEX matrixPointerOffset = 0;

	do {
		BASE* currRefPtr = &(ref.el[refPointerOffset]);
		CELL* currMatPtr = &(matrix[matrixPointerOffset]);
		FIMHW(currRefPtr, seq.el, (MATRIX_INDEX) (seq.length),
				currMatPtr, &maxPos, &currentMaxVal, refPointerOffset);
		refPointerOffset += sliceSize - 1;
		matrixPointerOffset = seqMax * (MATRIX_INDEX) refPointerOffset;
	} while (refPointerOffset < ref.length - sliceSize);

	//do the last part of the matrix:
	refPointerOffset = ref.length - sliceSize - 1;
	matrixPointerOffset = seqMax * (MATRIX_INDEX) refPointerOffset;
	BASE* currRefPtr = &(ref.el[refPointerOffset]);
	CELL* currMatPtr = &(matrix[matrixPointerOffset]);
	FIMHW(currRefPtr, seq.el, (MATRIX_INDEX) (seq.length),
			currMatPtr, &maxPos, &currentMaxVal, refPointerOffset);

	//DEBUG PERPOSES:
	//printf("maxPos: %i, %i\n\r", maxPos.row, maxPos.col);

	return maxPos;
}

