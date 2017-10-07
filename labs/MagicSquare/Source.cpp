#include <iostream>
#include <algorithm>

using namespace std;

bool isMagicSquare(int square[3][3])
{
	bool isMagic = true;
	int sumRow[3], sumColumn[3], sumDiag[2], data[9];
	int counter = 0;

	for (int i = 0; i < 3; i++)
	{
		if (!isMagic)
		{
			break;
		}

		int oneRow = 0, oneColumn = 0, oneDiag = 0, diagCounter = 0;
		for (int j = 0; j < 3; j++)
		{
			// Keep track of each piece of data in the square to check for 1-9 later
			data[counter] = square[i][j];
			counter++;
			// Get the row and column sums
			oneRow += square[i][j];
			oneColumn += square[j][i];
			// Get the diagonal sums
			if (i == 0)
			{
				oneDiag += square[i + diagCounter][j];
				diagCounter++;
			}
			else if (i == 2)
			{
				oneDiag += square[i - diagCounter][j];
				diagCounter++;
			}
		}

		// Assign values to arrays
		sumRow[i] = oneRow;
		sumColumn[i] = oneColumn;
		if (i == 0)
		{
			sumDiag[i] = oneDiag;
		}
		else if (i == 2)
		{
			// Since our diagonal array has only two elements need to deincrement i
			sumDiag[i - 1] = oneDiag;
		}

		// Do checks
		if (i > 1)
		{
			// Check to see that row and column sums are all equivalent
			if ((sumRow[i] != sumRow[i - 1]) || (sumColumn[i] != sumColumn[i - 1]))
			{
				isMagic = false;
			}
			// Once all the diagonals are calculated check to see the two are equivalent
			if ((i == 2) && (sumDiag[0] != sumDiag[1]))
			{
				isMagic = false;
			}
		}

	}

	// Only do this check if we didn't find problems previously
	if (isMagic)
	{
		sort(begin(data), end(data));
		// Need to have 1 through 9 only
		for (int i = 0; i < 9; i++)
		{
			if (data[i] != (i + 1))
			{
				isMagic = false;
			}
		}
	}

	return isMagic;
}

void displayResult(bool result)
{
	if (result)
	{
		cout << "Yes, it's a magic square!" << endl;
	}
	else
	{
		cout << "Nope, it's not a magic square." << endl;
	}
}

int main()
{
	int magicSquare[3][3] = { { 4, 9, 2 },
	{ 3, 5, 7 },
	{ 8, 1, 6 } };
	int notMagicSquare[3][3] = { { 4, 7, 2 },
	{ 3, 5, 9 },
	{ 8, 1, 4 } };
	displayResult(isMagicSquare(magicSquare));
	displayResult(isMagicSquare(notMagicSquare));

	return 0;
}