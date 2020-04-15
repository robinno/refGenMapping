#include "../functions.h"

BASE charToBase(char c) {
	switch (c) {
		case 'a':
		case 'A':
			return 1;
			break;
		case 'c':
		case 'C':
			return 2;
			break;
		case 'g':
		case 'G':
			return 3;
			break;
		case 't':
		case 'T':
			return 4;
			break;
	}
	return 0;
}

char baseToChar(BASE base) {
	switch (base) {
		case 1:
			return 'A';
			break;
		case 2:
			return 'C';
			break;
		case 3:
			return 'G';
			break;
		case 4:
			return 'T';
			break;
	}

	return 'N';
}
