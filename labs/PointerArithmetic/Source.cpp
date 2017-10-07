#include <iostream>

using namespace std;

void pointerArithmetic(int *arr, int size, int &average, int &high, int &low);

int main()
{
	const int SIZE = 5;
	int avg = 0, high = 0, low = 0;
	int data[SIZE] = { 50, 50, 30, 10, 40 };

	pointerArithmetic(data, SIZE, avg, high, low);

	cout << "Average: " << avg << endl;
	cout << "High: " << high << endl;
	cout << "Low: " << low << endl;

	return 0;
}

void pointerArithmetic(int * arr, int size, int & average, int & high, int & low)
{
	// Initialize high and low to use in loop
	high = *arr;
	low = *arr;
	for (int i = 0; i < size; i++)
	{
		average += *(arr + i);

		if (*(arr + i) > high)
		{
			high = *(arr + i);

		}
		if (*(arr + i) < low)
		{
			low = *(arr + i);
		}
	}

	average = average / size;
}
