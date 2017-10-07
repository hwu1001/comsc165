#include <iostream>

using namespace std;

int main()
{
	int numShares = 750;
	double initialPrice = 35.00, sellPrice = 31.15, paidTotal, sellTotal;

	paidTotal = numShares * initialPrice;
	sellTotal = numShares * sellPrice;

	cout << "Total amount paid for stock: " << paidTotal << endl;
	cout << "Total amount from selling stock: " << sellTotal << endl;
	cout << "Amout of money lost: " << paidTotal - sellTotal << endl;

	return 0;
}