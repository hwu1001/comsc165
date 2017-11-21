#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // for Sleep function

using namespace std;
// ‘Space’ is open cell in maze – robot can move here
// ‘Wall’ is closed cell in maze – robot cannot move here
// ‘Exit’ is exit from maze – robot escapes from maze here
// ‘Visited’ marks a ‘Space’ that has been visited by robot
// ‘Escaped’ marks an ‘Exit’ that has been visited by robot
enum Values { Space, Wall, Exit, Visited, Escaped };
Values maze[10][10];
int moves = 0; // counts number of robot moves
			   // startRow and startColumn are initial position of robot
void createMaze(int& startRow, int& startColumn) {
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			maze[i][j] = Wall;
	for (int j = 1; j < 10; j++)
		maze[1][j] = Space;
	for (int i = 1; i < 8; i++)
		maze[i][1] = Space;
	for (int j = 0; j < 5; j++)
		maze[7][j] = Space;
	for (int j = 2; j < 10; j++)
		maze[4][j] = Space;
	for (int i = 2; i < 4; i++)
		maze[i][5] = Space;
	maze[8][4] = Space;
	maze[7][0] = Exit;
	maze[4][9] = Exit;
	startRow = 1;
	startColumn = 9;
	return;
}

void showMaze(int robotRow, int robotColumn) {
	Sleep(500);
	system("cls");

	//Clear screen here – specific command depends on environment
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			if (i == robotRow && j == robotColumn)
				cout << 'X';
			else
				switch (maze[i][j]) {
				case Space:
					cout << ' ';
					break;
				case Wall:
					cout << '+';
					break;
				case Exit:
					cout << ' ';
					break;
				case Visited:
					cout << '.';
					break;
				case Escaped:
					cout << '!';
					break;

				}
		cout << endl;
	}
	cout << endl << moves << " moves" << endl;
	return;
}
void recursiveMove(int i, int j) {

	// your code here
	
	if (maze[i][j] == Wall || maze[i][j] == Visited || maze[i][j] == Escaped || i < 0 || i > 9 || j < 0 || j > 9)
	{
		return;
	}
	else
	{
		showMaze(i, j);
		moves = moves + 1;
		if (maze[i][j] == Space)
		{
			maze[i][j] = Visited;
		}
		else if (maze[i][j] == Exit)
		{
			maze[i][j] = Escaped;
		}
		// Order of these directions should not matter
		recursiveMove(i + 1, j);
		recursiveMove(i, j + 1);
		recursiveMove(i, j - 1);
		recursiveMove(i - 1, j);
	}

}

int main()
{
	int startRow, startColumn;
	createMaze(startRow, startColumn);
	recursiveMove(startRow, startColumn);

	return 0;

}
