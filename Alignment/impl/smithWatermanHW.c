#include "../smithWaterman.h"

/////////////////////
//PUBLIC FUNCTIONS://

void FillInMatrixHW(REF ref, SEQ seq, CELL matrix[refMax * seqMax], POS* maxPos) {
	CELL_VALUE max = 0;

	for (MATRIX_INDEX row = 1; row <= seq.length; row++) {
		for (MATRIX_INDEX col = 1; col <= ref.length; col++) {

			//calculate the possible  values
			CELL diagonalCELL = { matrix[(row - 1) * refMax + (col - 1)].value
					+ ((ref.el[col - 1] == seq.el[row - 1]) ? s : -s), 1 };
			CELL leftCELL = { matrix[(row) * refMax + (col - 1)].value - gp, 2 };
			CELL upCELL = { matrix[(row - 1) * refMax + (col)].value - gp, 3 };
			CELL zeroCELL = { 0, 0 };

			CELL upstreamA =
					(leftCELL.value > upCELL.value) ? leftCELL : upCELL;
			CELL upstreamB =
					(diagonalCELL.value > zeroCELL.value) ?
							diagonalCELL : zeroCELL;

			CELL Cell =
					(upstreamA.value > upstreamB.value) ? upstreamA : upstreamB;

			if (Cell.value > max) {
				*maxPos = (POS ) { row, col };
				max = Cell.value;
			}

			matrix[row * refMax + col] = Cell;
		}
	}
}

