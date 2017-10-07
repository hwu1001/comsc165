#include <iostream>

using namespace std;

int main()
{
	double income, tax = 0.0, tempNum;

	cout << "Enter your income: ";
	cin >> income;

	if (income <= 25000)
	{
		tax = 0;
	}
	else if (income <= 48000)
	{
		tax = (income - 25000) * 0.15;
	}
	else if (income <= 90000)
	{
		tax = (23000 * 0.15) + ((income - 48000) * 0.25);
	}
	else if (income <= 200000)
	{
		tax = (23000 * 0.15) + (42000 * 0.25) + ((income - 90000) * 0.30);
	}
	else
	{
		tax = (23000 * 0.15) + (42000 * 0.25) + (110000 * 0.30) + ((income - 200000) * 0.35);
	}
	//if (income > 200000.00)
	//{
	//	tempNum = income - 200000.00;
	//	tax = tempNum * 0.35;
	//}

	//if (income > 90000.00)
	//{
	//	tempNum = income - 90000.00;

	//	// If they have income over 200,000
	//	if (tempNum > 109999.00)
	//	{
	//		tax = tax + 33000.00;
	//	}
	//	else
	//	{
	//		tax = tax + (tempNum * 0.30);
	//	}
	//}

	//if (income > 48000.00)
	//{
	//	tempNum = income - 48000;

	//	// If they have income over 90,000
	//	if (tempNum > 41999.00)
	//	{
	//		tax = tax + 10500;
	//	}
	//	else
	//	{
	//		tax = tax + (tempNum * 0.25);
	//	}
	//}

	//if (income > 25000)
	//{
	//	tempNum = income - 25000.00;

	//	if (tempNum > 22999)
	//	{
	//		tax = tax + 3450;
	//	}
	//	else
	//	{
	//		tax = tax + (tempNum * 0.15);
	//	}
	//}

	cout << "Total taxes paid: " << tax << endl;

	return 0;
}