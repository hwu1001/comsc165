// Henry Wu
// COMSC 165
// Section 3015
// Homework #2

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h> // for Sleep and system
#include <ctime> // for time()
#include <cstdlib> // for rand()
#include <algorithm> // for remove()
#include <vector> // for begin() and end()

using namespace std;

const int MAX_SIZE = 10;
const char MAZE_CHAR = '*';

void createMaze(char mazeArray[][MAX_SIZE], int columns, int rows);
void showMaze(char maze[][MAX_SIZE], int robotCol, int robotRow);
void robot(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow);
bool isValidMove(char maze[][MAX_SIZE], int column, int row);

int main()
{
	int startRow = 1,
		startColumn = 0,
		endRow = 9,
		endColumn = 4,
		lastColumn,
		lastRow,
		nextColumn,
		nextRow,
		moves = 0;
	char maze[MAX_SIZE][MAX_SIZE];
	bool done = false;
	createMaze(maze, MAX_SIZE, MAX_SIZE);
	showMaze(maze, startColumn, startRow);
	lastColumn = startColumn;
	lastRow = startRow;

	do
	{
		robot(maze, lastColumn, lastRow, nextColumn, nextRow);
		// pause half second and clear the screen
		Sleep(500);
		system("cls");
		showMaze(maze, nextColumn, nextRow);
		lastColumn = nextColumn;
		lastRow = nextRow;

		if (nextColumn == endColumn && nextRow == endRow)
		{
			done = true;
		}

		moves++;
	} while (!done);

	cout << "Moves to complete the maze: " << moves << endl;

	return 0;
}

///<summary> Prompts user for file name (e.g., myFile.txt) then stores maze into 10 by 10 array. </summary>
///<param name="mazeArray"> A 10 by 10 array. </param>
///<returns> Nothing. 2D array returned in output parameter. </returns>
void createMaze(char mazeArray[][MAX_SIZE], int columns, int rows)
{
	string mazePath;
	ifstream mazeFile;

	cout << "Enter your file name that stores the maze (including .txt): ";
	getline(cin, mazePath);

	mazeFile.open(mazePath);

	if (!mazeFile)
	{
		cout << "Error opening file." << endl;
	}
	else
	{
		for (int i = 0; i < columns; i++)
		{
			string oneLine;
			// Get each line and iterate over it to store in array
			getline(mazeFile, oneLine);
			for (int j = 0; j < rows; j++)
			{
				mazeArray[i][j] = oneLine[j];
			}
		}
	}

	mazeFile.close();

	return;
}

///<summary> Displays the 10 by 10 maze given to it to the console. </summary>
///<param name="maze"> A 10 by 10 array. </param>
///<returns> Nothing. </returns>
void showMaze(char maze[][MAX_SIZE], int robotCol, int robotRow)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (i == robotRow && j == robotCol)
			{
				cout << "X";
			}
			else
			{
				cout << maze[i][j];
			}
		}
		cout << endl;
	}
}

void robot(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow)
{
	int max = 4;
	bool validMove = false;
	int randomNumber, tempColumn, tempRow;
	// Up, down, left, right - Didn't use enum because you can't edit an enum during runtime
	char directions[] = { 'u', 'd', 'l', 'r' };
	srand(time(0));

	// Get a random number between 0 and 3 for the direction
	// If the move is valid then update row and column
	// If it's not a valid move then remove that direction option
	// and repeat
	while (!validMove)
	{		
		randomNumber = rand() % max;
		switch (directions[randomNumber])
		{
		case 'u':
			tempColumn = lastColumn;
			tempRow = lastRow - 1;
			break;
		case 'd':
			tempColumn = lastColumn;
			tempRow = lastRow + 1;
			break;
		case 'l':
			tempColumn = lastColumn - 1;
			tempRow = lastRow;
			break;
		case 'r':
			tempColumn = lastColumn + 1;
			tempRow = lastRow;
			break;
		default:
			break;
		}

		if (isValidMove(maze, tempColumn, tempRow))
		{
			nextColumn = tempColumn;
			nextRow = tempRow;
			validMove = true;
		}
		else
		{
			auto arrayEnd = remove(begin(directions), end(directions), directions[randomNumber]);
			max--;
		}

	}
}

bool isValidMove(char maze[][MAX_SIZE], int column, int row)
{
	if (maze[row][column] == MAZE_CHAR)
	{
		return false;
	}
	else if (column < 0 || column > MAX_SIZE - 1)
	{
		return false;
	}
	else if (row < 0 || row > MAX_SIZE - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
	// It's not valid if
	// 1. The character we're moving to is a MAZE_CHAR
	// 2. The position is less than 0 (off the maze to the left or up)
	// 3. The position is greater than MAX_SIZE - 1 (off the maze to the right or down)
}
