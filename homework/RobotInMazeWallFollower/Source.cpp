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

void createMaze(char mazeArray[][MAX_SIZE]);
void getStartAndEndCoordinates(char mazeArray[][MAX_SIZE], int &startRow, int &startColumn, int &endRow, int &endColumn);
void showMaze(char maze[][MAX_SIZE], int robotCol, int robotRow, char direction);
void robot(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow, char &direction);
bool isValidMove(char maze[][MAX_SIZE], int column, int row);
void wallFollow(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow, int numChoices, char choicesArray[4], char &direction);
char pointRobot(char currentDirection, char relativeDirection);

int main()
{
	int startRow, startColumn, endRow, endColumn, lastColumn, lastRow, nextColumn, nextRow, moves = 0;
	char maze[MAX_SIZE][MAX_SIZE];
	char direction = NULL;
	bool done = false;

	createMaze(maze);
	getStartAndEndCoordinates(maze, startRow, startColumn, endRow, endColumn);
	showMaze(maze, startColumn, startRow, direction);
	lastColumn = startColumn;
	lastRow = startRow;

	do
	{
		robot(maze, lastColumn, lastRow, nextColumn, nextRow, direction);
		// pause half second and clear the screen
		Sleep(500);
		system("cls");
		showMaze(maze, nextColumn, nextRow, direction);
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

///<summary> Prompts user for file name (e.g., myFile.txt) then stores maze into an array. Note that MAX_SIZE determines the dimensions of the maze and is a global variable. </summary>
///<param name="mazeArray"> An array storing the maze. </param>
///<returns> Nothing. 2D array returned in output parameter. </returns>
void createMaze(char mazeArray[][MAX_SIZE])
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
		for (int i = 0; i < MAX_SIZE; i++)
		{
			string oneLine;
			// Get each line and iterate over it to store in array
			getline(mazeFile, oneLine);
			for (int j = 0; j < MAX_SIZE; j++)
			{
				mazeArray[i][j] = oneLine[j];
			}
		}
	}

	mazeFile.close();

	return;
}

///<summary> Prompts user for the start row/column and end row/column for the maze. </summary>
///<param name="maze"> An array storing the maze. </param>
///<param name="startRow"> The start row position of the maze. </param>
///<param name="startColumn"> The start column position of the maze. </param>
///<param name="endRow"> The end row position of the maze. </param>
///<param name="endColumn"> The end column position of the maze. </param>
///<returns> Nothing </returns>
void getStartAndEndCoordinates(char maze[][MAX_SIZE], int &startRow, int &startColumn, int &endRow, int &endColumn)
{
	bool valid = false;

	while (!valid)
	{
		cout << "What is the starting row for the robot? ";
		cin >> startRow;
		cout << "What is the starting column for the robot? ";
		cin >> startColumn;
		valid = isValidMove(maze, startColumn, startRow);
		if (!valid)
		{
			cout << "Invalid input" << endl;
		}
	}

	valid = false;
	while (!valid)
	{
		cout << "What is the ending row for the robot? ";
		cin >> endRow;
		cout << "What is the ending column for the robot? ";
		cin >> endColumn;
		valid = isValidMove(maze, endColumn, endRow);
		if (!valid)
		{
			cout << "Invalid input" << endl;
		}
	}
}

///<summary> Displays the 10 by 10 maze given to it to the console. </summary>
///<param name="maze"> A 10 by 10 array. </param>
///<param name="robotCol"> The current column the robot is in. </param>
///<param name="robotRow"> The current row the robot is in. </param>
///<param name="direction"> The direction the robot is facing. 'u' - Up, 'd' - down, 'l' - left, 'r' - right </param>
///<returns> Nothing. </returns>
void showMaze(char maze[][MAX_SIZE], int robotCol, int robotRow, char direction)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (i == robotRow && j == robotCol)
			{
				switch (direction)
				{
				case 'u':
					cout << "^";
					break;
				case 'd':
					cout << "V";
					break;
				case 'l':
					cout << "<";
					break;
				case 'r':
					cout << ">";
					break;
				default:
					cout << "X";
					break;
				}
			}
			else
			{
				cout << maze[i][j];
			}
		}
		cout << endl;
	}
}

///<summary> Controls the movement of the robot in the maze. </summary>
///<param name="maze"> A 10 by 10 array. </param>
///<param name="lastColumn"> Robot's last column position </param>
///<param name="lastRow"> Robot's last row position </param>
///<param name="nextColumn"> Robot's next column position </param>
///<param name="nextRow"> Robot's next row position </param>
///<param name="direction"> Robot's current direction </param>
///<returns> Nothing. </returns>
void robot(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow, char &direction)
{
	int max = 4;
	bool validMove = false;
	int randomNumber = 0, tempColumn, tempRow;
	// Up, down, left, right - Didn't use enum because you can't edit an enum during runtime
	char directions[] = { 'u', 'd', 'l', 'r' };

	while (!validMove)
	{
		// If we don't have a direction then get a random number between 0 and 3 for the direction
		// If the move is valid then update row and column
		// If it's not a valid move then remove that direction option
		// and repeat
		if (direction == NULL)
		{
			srand(time(0));
			randomNumber = rand() % max;
			direction = directions[randomNumber];
			switch (direction)
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
				direction = NULL;
			}
		}
		else
		{
			wallFollow(maze, lastColumn, lastRow, tempColumn, tempRow, max, directions, direction);
			nextColumn = tempColumn;
			nextRow = tempRow;
			validMove = true; // wallFollow() checks to see that its moves are valid
		}



	}
}

///<summary> Determines whether the position the robot would move to is valid or not. </summary>
///<param name="maze"> A 10 by 10 array containing the maze </param>
///<param name="column"> Current column position of the robot </param>
///<param name="row"> Current row position of the robot </param>
///<returns> If the robot would move into a wall or off the maze return false, otherwise true. </returns>
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
}

///<summary> Right wall follow algorithm:
///1. If there's no direction set - choose a valid, random one
///2. If there's a wall to the right of the robot's direction - go forward(the direction the robot is currently going in)
///3. If there's no wall to the right of the robot - then go right
///4. If the robot cannot go forward or right then go left
///5. If the robot cannot go forward, right, or left then go back
///</summary>
///<param name="maze"> 2D array that stores the maze. </param>
///<param name="lastColumn"> Robot's last column position </param>
///<param name="lastRow"> Robot's last row position </param>
///<param name="nextColumn"> Robot's next column position </param>
///<param name="nextRow"> Robot's next row position </param>
///<param name="numChoices"> Number of choices left in choices array (1-4) </param>
///<param name="choicesArray"> Array of choices ('u', 'd', 'l', 'r') </param>
///<param name="direction"> The current direction of the robot</param>
///<returns> Returns the new direction of the robot. 'u' - Up, 'd' - Down, 'l' - Left, 'r' - Right</returns>
void wallFollow(char maze[][MAX_SIZE], int lastColumn, int lastRow, int &nextColumn, int &nextRow, int numChoices, char choicesArray[4],  char &direction)
{
	int randomNumber, colRight, rowRight, colForward, rowForward, colLeft, rowLeft, colBack, rowBack;
	char back;

	// Checking just in case
	if (direction == NULL)
	{
		srand(time(0));
		randomNumber = rand() % numChoices;
		direction = choicesArray[randomNumber];
		return;
	}

	// Find coordinates relative to the robot's current direction
	switch (direction)
	{
	case 'u':
		colRight = lastColumn + 1;
		rowRight = lastRow;
		colForward = lastColumn;
		rowForward = lastRow - 1;
		colLeft = lastColumn - 1;
		rowLeft = lastRow;
		colBack = lastColumn;
		rowBack = lastRow + 1;
		back = 'd';
		break;
	case 'd':
		colRight = lastColumn - 1;
		rowRight = lastRow;
		colForward = lastColumn;
		rowForward = lastRow + 1;
		colLeft = lastColumn + 1;
		rowLeft = lastRow;
		colBack = lastColumn;
		rowBack = lastRow - 1;
		back = 'u';
		break;
	case 'l':
		colRight = lastColumn;
		rowRight = lastRow - 1;
		colForward = lastColumn - 1;
		rowForward = lastRow;
		colLeft = lastColumn;
		rowLeft = lastRow + 1;
		colBack = lastColumn + 1;
		rowBack = lastRow;
		back = 'r';
		break;
	case 'r':
		colRight = lastColumn;
		rowRight = lastRow + 1;
		colForward = lastColumn + 1;
		rowForward = lastRow;
		colLeft = lastColumn;
		rowLeft = lastRow - 1;
		colBack = lastColumn - 1;
		rowBack = lastRow;
		back = 'l';
		break;
	default:
		break;
	}

	if (maze[rowRight][colRight] == MAZE_CHAR && isValidMove(maze, colForward, rowForward))
	{
		// Keep going forward in the same direction
		direction = direction;
		nextColumn = colForward;
		nextRow = rowForward;
	}
	// Don't try to turn right if ahead of the robot is off the map, since then the robot can just go into a circle infinitely
	else if (maze[rowRight][colRight] == ' ' && (rowForward >= 0 && rowForward <= MAX_SIZE - 1) && (colForward >= 0 && colForward <= MAX_SIZE - 1) && isValidMove(maze, colRight, rowRight))
	{
		direction = pointRobot(direction, 'r');
		nextColumn = colRight;
		nextRow = rowRight;
	}
	else if (isValidMove(maze, colLeft, rowLeft))
	{
		direction = pointRobot(direction, 'l');
		nextColumn = colLeft;
		nextRow = rowLeft;
	}
	else
	{
		// No need to check validity of movement back since we just came from that position
		direction = back;
		nextColumn = colBack;
		nextRow = rowBack;
	}

	return;
}

///<summary> Points the robot in a new direction based on its current direction and the direction it wants to turn. </summary>
///<param name="currentDirection"> The current direction of the robot </param>
///<param name="relativeDirection"> The direction the robot would like to turn </param>
///<returns> Returns the new direction of the robot. 'u' - Up, 'd' - Down, 'l' - Left, 'r' - Right</returns>
char pointRobot(char currentDirection, char relativeDirection)
{
	char newDirection;
	switch (currentDirection)
	{
	case 'd':
		if (relativeDirection == 'r')
		{
			newDirection = 'l';
		}
		else if (relativeDirection == 'l')
		{
			newDirection = 'r';
		}
		else
		{
			newDirection = relativeDirection;
		}
		break;
	case 'l':
		if (relativeDirection == 'r')
		{
			newDirection = 'u';
		}
		else if (relativeDirection == 'l')
		{
			newDirection = 'd';
		}
		else
		{
			newDirection = relativeDirection;
		}
		break;
	case 'r':
		if (relativeDirection == 'r')
		{
			newDirection = 'd';
		}
		else if (relativeDirection == 'l')
		{
			newDirection = 'u';
		}
		else
		{
			newDirection = relativeDirection;
		}
		break;
	default:
		// All directions relative to "up" are the same for the maze and the robot
		newDirection = relativeDirection;
		break;
	}

	return newDirection;
}