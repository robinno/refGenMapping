#include "headers/displayForDebug.h"

void displayMatrix(BASE ref[refMax], REF_INDEX refLength, BASE seq[seqMax],
		SEQ_INDEX seqLength, CELL matrix[seqMax][refMax]) {
	printf("\n\r\n\r");

	printf("\t\t");
	for (REF_INDEX i = 0; i < refLength; i++) {
		if (i == 0)
			printf("\t");
		else
			printf("%i\t", ref[i]);
	}
	printf("\n\r");

	printf("\t\t");
	for (REF_INDEX i = 0; i < refLength; i++) {
		printf("--------");
	}
	printf("\n\r");

	for (SEQ_INDEX i = 0; i < seqLength; i++) {
		if (i == 0)
			printf("\t|\t");
		else
			printf("%i\t|\t", seq[i]);

		for (REF_INDEX j = 0; j < refLength; j++) {
			printf("%i\t", matrix[i][j].value);
		}
		printf("\n\r");
	}
	printf("\n\r\n\r");
}

void displayLL(CELL* cell) {
	if (cell->prevCell == NULL) {
		printf("%i (%i,%i)\n\r", cell->value, cell->pos.row, cell->pos.col);
		return;
	}
	printf("%i (%i,%i) -> ", cell->value, cell->pos.row, cell->pos.col);
	displayLL(cell->prevCell);
}

void displayMax(POS maxPos, CELL_VALUE max){
	printf("Position of maximum = row %i, column %i => with maximum %i\n\r\n\r",
				maxPos.row, maxPos.col, max);
}
