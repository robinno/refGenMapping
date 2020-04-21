#include "../ConversionFunctions.h"

BASE charToBase(char c) {
	switch (c) {
	case 'a':
	case 'A':
		return A;
		break;
	case 'c':
	case 'C':
		return C;
		break;
	case 'g':
	case 'G':
		return G;
		break;
	case 't':
	case 'T':
		return T;
		break;
	}
	return 0;
}

char baseToChar(BASE base) {
	switch (base) {
	case A:
		return 'A';
		break;
	case C:
		return 'C';
		break;
	case G:
		return 'G';
		break;
	case T:
		return 'T';
		break;
	}

	return 'N';
}
