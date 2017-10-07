// Lab - Magic Square 2 - 09/05/2017
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_SIZE = 4, MAX_INPUT = MAX_SIZE * MAX_SIZE;
// Reason we have to have the array specified in this way below is so that the array doesn't decay
// https://stackoverflow.com/questions/26182907/range-based-for-loop-on-array-passed-to-non-main-function
bool isSquareInputValid(int dimension, int value, int(&input)[MAX_INPUT]);
void getSquareValues(int dimension, int square[][MAX_SIZE]);
int getMagicNumber(int dimension);
void computeRowAndColSums(int dimension, int square[][MAX_SIZE], int sums[MAX_SIZE + MAX_SIZE]);
void computeDiagSums(int dimension, int square[][MAX_SIZE], int sums[2]);
bool isMagicSquare(int magicNum, int rowAndColSums[MAX_SIZE + MAX_SIZE], int diagSums[2]);

int main()
{
	int magicSquare[MAX_SIZE][MAX_SIZE], rowColSums[MAX_SIZE + MAX_SIZE], diagSums[2];

	getSquareValues(MAX_SIZE, magicSquare);
	computeRowAndColSums(MAX_SIZE, magicSquare, rowColSums);
	computeDiagSums(MAX_SIZE, magicSquare, diagSums);

	if (isMagicSquare(getMagicNumber(MAX_SIZE), rowColSums, diagSums))
	{
		cout << "It is a magic square!" << endl;
	}
	else
	{
		cout << "Not a magic square." << endl;
	}

	return 0;
}

bool isSquareInputValid(int dimension, int value, int(&input)[MAX_INPUT])
{
	if (value < 1 || value > (dimension * dimension))
	{
		return false;
	}

	// Check to see if the current input has already been input into the square
	int *temp = find(begin(input), end(input), value);

	if (temp != end(input))
	{
		return false;
	}

	return true;
}

void getSquareValues(int dimension, int square[][MAX_SIZE])
{
	int inputArray[MAX_INPUT];
	int count = 0;
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			bool validInput = false;
			while (!validInput)
			{
				cout << "Enter a value for the square at " << "[" << i << "]" << "[" << j << "]:" << endl;
				cin >> square[i][j];

				if (isSquareInputValid(dimension, square[i][j], inputArray))
				{
					validInput = true;
					inputArray[count] = square[i][j];
				}
				else
				{
					cout << "Invalid input." << endl;
				}
			}
			count++;
		}
	}
}

int getMagicNumber(int dimension)
{
	int sum = 0;

	for (int i = 1; i <= (dimension * dimension); i++)
	{
		sum += i;
	}

	return (sum / dimension);
}

void computeRowAndColSums(int dimension, int square[][MAX_SIZE], int sums[MAX_SIZE + MAX_SIZE])
{
	int count = 0;
	for (int i = 0; i < dimension; i++)
	{
		int oneRow = 0, oneCol = 0;
		for (int j = 0; j < dimension; j++)
		{
			oneRow += square[i][j];
			oneCol += square[j][i];
		}
		sums[count] = oneRow;
		count++;
		sums[count] = oneCol;
		count++;
	}
}

void computeDiagSums(int dimension, int square[][MAX_SIZE], int sums[2])
{
	
	for (int i = 0; i < dimension; i++)
	{
		int oneDiag = 0, diagCounter = 0;
		for (int j = 0; j < dimension; j++)
		{
			if (i == 0)
			{
				oneDiag += square[i + diagCounter][j];
				diagCounter++;
			}
			else if (i == (dimension - 1))
			{
				oneDiag += square[i - diagCounter][j];
				diagCounter++;
			}
			else
			{
				break;
			}
		}

		if (i == 0)
		{
			sums[0] = oneDiag;
		}
		else if (i == (dimension - 1))
		{
			sums[1] = oneDiag;
		}
	}
}

bool isMagicSquare(int magicNum, int rowAndColSums[MAX_SIZE + MAX_SIZE], int diagSums[2])
{
	bool isMagic = true;
	for (int i = 0; i < 2; i++)
	{
		if (diagSums[i] != magicNum)
		{
			isMagic = false;
			break;
		}
	}
	// Don't check row and column sums if diagonal sums are already bad
	if (isMagic)
	{
		for (int i = 0; i < (MAX_SIZE + MAX_SIZE); i++)
		{
			if (rowAndColSums[i] != magicNum)
			{
				isMagic = false;
				break;
			}
		}
	}

	return isMagic;
}
