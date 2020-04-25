#include "../displayForDebug.h"

//////////////////////
//PRIVATE FUNCTIONS://


//translating coordinates to address
static inline MATRIX_INDEX coordToAddr(SEQ_INDEX row, REF_INDEX column) {
	return (((MATRIX_INDEX) row) * refMax + (MATRIX_INDEX) column);
}

/////////////////////
//PUBLIC FUNCTIONS://

void displayMatrix(REF ref, SEQ seq, CELL matrix[seqMax * refMax]) {
	printf("\n\r\n\r");

	printf("Length of ref: %i", ref.length);

	printf("\n\r\n\r");

	printf("\t\t");
	for (REF_INDEX i = 0; i <= ref.length && i < 15; i++) {
		if (i == 0)
			printf("\t");
		else
			printf("%i\t", ref.el[i - 1]);
	}
	printf("\n\r");

	printf("\t");
	for (REF_INDEX i = 0; i <= ref.length && i < 15; i++) {
		printf("--------");
	}
	printf("\n\r");

	for (SEQ_INDEX i = 0; i <= seq.length && i < 15; i++) {
		if (i == 0)
			printf("\t|\t");
		else
			printf("%i\t|\t", seq.el[i - 1]);

		for (REF_INDEX j = 0; j <= ref.length && j < 15; j++) {
			printf("%i\t", matrix[coordToAddr(i, j)].value);
		}
		printf("\n\r");
	}
	printf("\n\r\n\r");
}

void displayMax(POS maxPos, CELL_VALUE max) {
	printf("Position of maximum = row %i, column %i => with maximum %i\n\r\n\r",
			maxPos.row, maxPos.col, max);
}

