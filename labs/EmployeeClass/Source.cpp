#include <iostream>
#include <string>
#include <iomanip>
#include "Employee.h"

using namespace std;

int main()
{
	const int MAX_SIZE = 4;
	int longestNameLength = 0;
	string lastName;
	double payRate, hoursWorked;
	Employee employees[MAX_SIZE] = { Employee("Jackson"),
		Employee("Rodriguez"),
		Employee("Chang"),
		Employee("Demos") };


	for (int i = 0; i < MAX_SIZE; i++)
	{
		cout << "For employee " << employees[i].getLastName() << " please enter the following." << endl;
		cout << "Enter pay rate: ";
		cin >> payRate;
		cout << "Enter number of hours worked: ";
		cin >> hoursWorked;
		employees[i].setHourlyPay(payRate);
		employees[i].setNumHoursWorked(hoursWorked);
		if (employees[i].getLastName().length() > longestNameLength)
		{
			longestNameLength = employees[i].getLastName().length();
		}
	}

	cout << setprecision(2) << fixed;
	cout << "Employee" << setw(6) << "Name" << setw(7 + longestNameLength) << "Gross pay" << endl;
	cout << "========" << setw(6) << "====" << setw(7 + longestNameLength) << "=========" << endl;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		// 9 is for "mployee" plus 2 spaces between columns (assumes there are 9 or fewer employees)
		int spaceForName = 9 + employees[i].getLastName().length();
		// 4 is for "$ " and 2 spaces between columns
		int spaceForPay = longestNameLength - employees[i].getLastName().length() + 4;

		cout << (i + 1) << setw(spaceForName) << employees[i].getLastName() << setw(spaceForPay) << "$ " << right << employees[i].totalPay() << endl;
	}

	return 0;
}