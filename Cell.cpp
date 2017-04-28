#include "Cell.h"

Cell::Cell(int value) 
			: value(value)
			, given(value == 0 ? false : true) {
	for (int i = 0; i < 9; i++) {
		candidateList[i] = i + 1;
	}
}
Cell::~Cell()
{
}
