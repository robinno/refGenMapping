#include "topheaders/functions.h"

BASE charToBase(char c){
	if(c == 'a' || c == 'A') return 1;
	if(c == 'g' || c == 'G') return 2;
	if(c == 'c' || c == 'C') return 3;
	if(c == 't' || c == 'T') return 4;
	else return 0;
}
