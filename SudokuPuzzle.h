#pragma once

#include <iostream>
#include <fstream>
#include "CellGroup.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	CellGroup rows[9];
	CellGroup columns[9];
	CellGroup blocks[9];

	void InitialiseCellGroups(int* grid);
	void Output() const;
};

