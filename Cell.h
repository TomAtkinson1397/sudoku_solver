#pragma once
#include <vector>

using namespace std;

class Cell
{
public:
	explicit Cell(int value);
	~Cell();

	void SetValue(int value) {
		this->value = value;
	}

	int GetValue() const {
		return this->value;
	}
	const int GetCandidate(int index) const {
		return this->candidateList[index];
	}

	void SetCandidateAt(int index, int value) {
		this->candidateList[index] = value;
	}

	bool IsGiven() const {
		return this->given;
	}

private:
	int candidateList[9];
	int value;
	bool given;
};

