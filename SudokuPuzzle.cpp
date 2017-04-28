#include "SudokuPuzzle.h"
#include <Windows.h>
#include <fstream>
#include <String>

using namespace std;

SudokuPuzzle::SudokuPuzzle(void) 
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	//init grid from ifstream
	ifstream fin(filenameIn);
	int value = 0;
	int grid[81];
	if (fin.is_open()) {
		while (fin) {
			for (int y = 0; y < 9; y++) {
				for (int x = 0; x < 9; x++) {
					fin >> grid[x + y * 9];
				}
			}
		}
	}
	InitialiseCellGroups(grid);
	bool solved = false;

	// You will need to read the values of the Sudoku puzzle into your data structure
	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	int passes = 0;
	int compares = 0;
	while (!solved) {
		int setCells = 0;
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (!rows[y].GetCell(x)->IsGiven()) {
					if (rows[y].GetCell(x)->GetValue() == 0) {
						Cell* currentCell = rows[y].GetCell(x);
						//int* candidates = currentCell->GetCandidates();
						//remove values from candidate current cell candidate list to narrow down
						for (int i = 0; i < 9; i++) {
							//potentially check for candidates[i] == 0
							int val = columns[x].GetCell(i)->GetValue();
							if (val != 0) {
								currentCell->SetCandidateAt(val - 1, 0);
							}
							val = rows[y].GetCell(i)->GetValue();
							if (val != 0) {
								currentCell->SetCandidateAt(val - 1, 0);
							}
							val = blocks[((y / 3) * 3) + (x / 3)].GetCell(i)->GetValue();
							if (val != 0) {
								currentCell->SetCandidateAt(val - 1, 0);
							}
						}

						//count candidates on cell
						int candidateCount = 0;
						int lastVal = 0;
						for (int i = 0; i < 9; i++) {
							if (currentCell->GetCandidate(i) != 0) {
								candidateCount++;
								lastVal = currentCell->GetCandidate(i);
							}
						}
						if (candidateCount == 1) {
							rows[y].GetCell(x)->SetValue(lastVal);
							setCells++;
						}
					}
					else {
						setCells++;
					}
				}
				else {
					setCells++;
				}
			}
		}
		if (setCells == 81) {
			break;
		}
		passes++;
	}
	cout << passes << " passes" << endl;
	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	cout << "Time: " << time << endl;
	Output();  // Output the solved puzzle
}

void SudokuPuzzle::InitialiseCellGroups(int* grid) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			int currentIndex = x + y * 9;

			Cell* newCell = new Cell(grid[currentIndex]);
			rows[y].SetCell(x, newCell);
			columns[x].SetCell(y, newCell);

			int blockIndex = ((y / 3) * 3) + (x / 3);
			int indexInBlock = (x % 3) + ((y % 3) * 3);
			blocks[blockIndex].SetCell(indexInBlock, newCell);
		}
	}
}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if(fout.is_open())
	{
		for(int y = 0; y < 9; ++y)
		{
			for(int x = 0; x < 9; ++x)
			{
				cout << rows[y].GetCell(x)->GetValue() << " ";
				fout << rows[y].GetCell(x)->GetValue() << " ";
			}
			cout << endl;
			fout << endl;
		}
		fout.close();
	}
}
