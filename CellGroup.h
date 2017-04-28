#pragma once

#include "Cell.h"

class CellGroup
{
public:
	CellGroup();
	~CellGroup();

	void SetCell(int index, Cell* cell);
	Cell* GetCell(int index) const;

private:
	Cell* cells[9];
};

