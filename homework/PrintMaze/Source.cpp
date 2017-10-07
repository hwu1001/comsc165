// Henry Wu
// COMSC 165
// Section 3015
// Homework #1

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void getMaze(char mazeArray[10][10]);
void displayMaze(char maze[10][10]);

int main()
{
	char maze[10][10];
	getMaze(maze);
	displayMaze(maze);
	return 0;
}

///<summary> Prompts user for file name (e.g., myFile.txt) then stores maze into 10 by 10 array. </summary>
///<param name="mazeArray"> A 10 by 10 array. </param>
///<returns> Nothing. 2D array returned in output parameter. </returns>
void getMaze(char mazeArray[10][10])
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
		for (int i = 0; i < 10; i++)
		{
			string oneLine;
			int j = 0;
			// Get each line and iterate over it to store in array
			getline(mazeFile, oneLine);
			for (char piece : oneLine)
			{
				mazeArray[i][j] = piece;
				j++;
			}
		}
	}

	mazeFile.close();

	return;
}

///<summary> Displays the 10 by 10 maze given to it to the console. </summary>
///<param name="maze"> A 10 by 10 array. </param>
///<returns> Nothing. </returns>
void displayMaze(char maze[10][10])
{
	cout << "Here's the maze in the given file:" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
}