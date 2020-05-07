#include "../smithWatermanHW.h"
#include "../../PARAMS.h"

/////////////////////
//PUBLIC FUNCTIONS://
MATRIX_INDEX FillInHW(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[refMax * seqMax]) {
#pragma HLS data_pack variable=matrix
	//#pragma HLS PIPELINE

	//maximum value searching:
	CELL_VALUE currentMaxVal = 0;
	POS maxPos = { 0, 0 };

	//diagonal registers:
	CELL_VALUE currDiagonal[seqMax];
	CELL_VALUE prevDiagonal[seqMax];
	CELL_VALUE prevprevDiagonal[seqMax];

	//init all on zero:
	for (SEQ_INDEX index = 0; index < seqMax; index++) {
		#pragma HLS UNROLL
		prevprevDiagonal[index] = 0;
		prevDiagonal[index] = 0;
		currDiagonal[index] = 0;
	}

	//start at second column:
	COL: for (MATRIX_INDEX currCol = 2; currCol < (refLength + seqLength);
			currCol++) {
	#pragma HLS loop_tripcount min=5000 avg=5150 max=5700
//#pragma HLS loop_merge
		#pragma HLS PIPELINE

		//new diagonal generation loop
		DIAG: for (SEQ_INDEX i = 1; i < seqMax; i++) {
			#pragma HLS UNROLL
			SEQ_INDEX row = i;
			MATRIX_INDEX col = currCol - i;

			if (i < seqLength && col != 0 && col <= refLength) { //no edge cases

				/////////////////////
				//Generation
				CELL_VALUE sim = (ref[col - 1] == seq[row - 1]) ? s : -s;

				//calculate the possible  values
				CELL diagonalCELL = { prevprevDiagonal[i - 1] + sim, 1 };
				CELL leftCELL = { prevDiagonal[i] - gp, 2 };
				CELL upCELL = { prevDiagonal[i - 1] - gp, 3 };
				CELL zeroCELL = { 0, 0 };

				CELL upstreamA =
						(leftCELL.value > upCELL.value) ? leftCELL : upCELL;
				CELL upstreamB =
						(diagonalCELL.value > zeroCELL.value) ?
								diagonalCELL : zeroCELL;

				CELL cell =
						(upstreamA.value > upstreamB.value) ?
								upstreamA : upstreamB;
				////////////////////

				//storing
				currDiagonal[i] = cell.value;
				matrix[row + col * seqMax] = cell;

				//maximum value search:
				if (cell.value > currentMaxVal) {
					maxPos = (POS ) { row, (REF_INDEX) col };
					currentMaxVal = cell.value;
				}
			}
		}

		//shift values:
		SHIFT: for (SEQ_INDEX j = 0; j < seqMax; j++) {
			#pragma HLS UNROLL
			prevprevDiagonal[j] = prevDiagonal[j];
			prevDiagonal[j] = currDiagonal[j];
		}
	}

	return maxPos.row + ((MATRIX_INDEX) maxPos.col) * seqMax;
}
