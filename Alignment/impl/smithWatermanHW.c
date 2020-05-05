#include "../smithWatermanHW.h"

/////////////////////
//PUBLIC FUNCTIONS://
void FIMHW(BASE ref[sliceSize], BASE seq[seqMax], MATRIX_INDEX seqLength,
		CELL matrix[sliceSize * seqMax], POS* maxPos, CELL_VALUE* currentMaxVal, REF_INDEX coloffset) {
	CELL localMatrix[sliceSize * seqMax];
#pragma HLS data_pack variable=matrix
#pragma HLS data_pack variable=maxPos

#pragma HLS PIPELINE

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
#pragma HLS loop_tripcount min=75 max=300 avg=150

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

