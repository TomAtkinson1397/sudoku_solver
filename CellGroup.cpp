#include "CellGroup.h"
#include "Cell.h"

CellGroup::CellGroup()
{
	for (int i = 0; i < 9; i++) {
		cells[i] = 0;
	}
}


CellGroup::~CellGroup()
{
}

void CellGroup::SetCell(int index, Cell* cell)
{
	cells[index] = cell;
}

Cell* CellGroup::GetCell(int index) const {
	return cells[index];
}
