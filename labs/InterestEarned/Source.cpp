#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	double principal, interestRate, numCompounded, finalBalance, interest;
	int numLength = 1, tempNum;

	cout << "Enter the principal: ";
	cin >> principal;
	cout << "Enter the interest rate: ";
	cin >> interestRate;
	cout << "Enter the number of times the interest is compounded: ";
	cin >> numCompounded;

	finalBalance = principal * pow((1 + ((interestRate / 100) / numCompounded)), numCompounded);

	interest = finalBalance - principal;

	if (principal > finalBalance)
	{
		tempNum = static_cast<int>(principal);
	}
	else
	{
		tempNum = static_cast<int>(finalBalance);
	}

	while (tempNum /= 10)
	{
		numLength++;
	}

	// Add 3 for the decimal point and 2 numbers after decimal
	numLength = numLength + 3;

	// Two decimal points for each number
	cout << setprecision(2) << fixed;
	// Use setw after the labels so that the $ sign stays with the numbers
	cout << "Principal: " << setw(6) << "$" << setw(numLength) << right << principal << endl;
	cout << "Interest: " << setw(7) << "$" << setw(numLength) << right << interest << endl;
	cout << "Final balance: " << setw(2) << "$" << setw(numLength) << right << finalBalance << endl;

	return 0;
}