#include <iostream>
#include <cmath>
#include <Windows.h>
#include <time.h>

using namespace std;

bool isPrime(int);

int main()
{
	int maxVal, count = 0, numPrimes = 0;

	cout << "Enter a maximum value: ";
	cin >> maxVal;
	time_t end = time(NULL) + 60;
	clock_t t = clock();

	for (int i = 0; i <= maxVal; i++)
	{
		if (time(NULL) >= end)
		{
			break;
		}

		if (isPrime(i))
		{
			//cout << i << endl;
			numPrimes++;
			//count++;
		}

		//if (count == 10)
		//{
		//	Sleep(5000);
		//	system("cls");
		//	// reset count
		//	count = 0;
		//}
	}

	t = clock() - t;
	cout << "Total number of primes: " << numPrimes << endl;
	cout << "Time passed in seconds: " << (float(t)) / CLOCKS_PER_SEC << endl;
	return 0;
}

bool isPrime(int value)
{
	if (value < 2) return false;
	if (value == 2) return true;
	if (value % 2 == 0) return false;

	for (int i = 3; i <= sqrt(value); i++)
	{
		if (value % i == 0) return false;
	}

	return true;
}