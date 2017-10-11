#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

int getInput(string prompt, int min, int max);
void displayDate(Date date);

int main()
{
	int day = 0, month = 0, year = 0, diff;
	int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	year = getInput("Enter the first date's year: ", 0, INT_MAX);
	month = getInput("Enter the first date's month: ", 1, 12);
	day = getInput("Enter the first date's day: ", 1, monthDays[month - 1]);
	cout << endl;

	Date date1(month, day, year);

	year = getInput("Enter the second date's year: ", 0, INT_MAX);
	month = getInput("Enter the second date's month: ", 1, 12);
	day = getInput("Enter the second date's day: ", 1, monthDays[month - 1]);
	cout << endl;

	Date date2(month, day, year);

	cout << "Results:" << endl;
	cout << "Increment dates:" << endl;
	date1++;
	date2++;
	cout << "Date 1: ";
	displayDate(date1);
	cout << "Date 2: "; 
	displayDate(date2);
	cout << "Decrement dates:" << endl;
	date1--;
	date2--;
	cout << "Date 1: ";
	displayDate(date1);
	cout << "Date 2: ";
	displayDate(date2);

	if (date1 > date2)
	{
		cout << "Date 1 is greater than date 2." << endl;
	}
	else
	{
		cout << "Date 2 is greater than date 1." << endl;
	}
	diff = date1 - date2;
	cout << "The difference between the two dates is " << diff << " days." << endl;

	return 0;
}

int getInput(string prompt, int min, int max)
{
	bool done = false;
	int val = 0;
	while (!done)
	{
		cout << prompt;
		cin >> val;

		if (val < min || val > max)
		{
			cout << "Invalid input." << endl;
		}
		else
		{
			done = true;
		}
	}
	return val;
}

void displayDate(Date date)
{
	cout << date.getMonth() << "/" << date.getDay() << "/" << date.getYear() << endl;
}
