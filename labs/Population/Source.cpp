// Programming Challenge 5-27

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	fstream file;
	int population, year = 1910;
	string popString;

	file.open("Population.txt");

	if (file)
	{
		cout << "HOBOKEN POPULATION GROWTH" << endl;
		cout << "(each * represents 1000 people)" << endl;
		while (file >> population)
		{
			popString.clear();
			for (int i = 0; i < (population / 1000); i++)
			{
				popString += "*";
			}
			cout << year << " " << popString << endl;
			year += 20;
		}
	}
	else
	{
		cout << "Error opening file.";
	}

	file.close();

	return 0;
}