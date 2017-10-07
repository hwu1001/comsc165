#include <iostream>
#include "DayOfYear.h"

using namespace std;

int main()
{
	int choice = 0;
	do
	{
		cout << "Enter a number between 1 and 365 to get the month/day (Enter 0 to quit): ";
		cin >> choice;

		if (choice != 0 && (choice < 1 || choice > 365) && !cin.fail())
		{
			cout << "Invalid day. Please enter again." << endl;
		}
		else if (!cin.fail() && choice != 0)
		{
			DayOfYear day(choice);
			day.print();
		}

	} while (!cin.fail() && choice != 0);
}