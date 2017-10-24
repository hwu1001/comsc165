#include <iostream>
#include <string>

using namespace std;

void selectionSort(string arr[], int size);
void swapStr(string* first, string* second);

int main()
{
	const int SIZE = 20;

	string name[SIZE] =
	{ "Collins, Bill", "Smith, Bart", "Michalski, Joe", "Griffin, Jim",
		"Sanchez, Manny", "Rubin, Sarah", "Taylor, Tyrone", "Johnson, Jill",
		"Allison, Jeff", "Moreno, Juan", "Wolfe, Bill", "Whitman, Jean",
		"Moretti, Bella", "Wu, Hong", "Patel, Renee", "Harrison, Rose",
		"Smith, Cathy", "Conroy, Pat", "Kelly, Sean", "Holland, Beth" };

	selectionSort(name, SIZE);

	for (string const &n : name)
	{
		cout << n << endl;
	}

	return 0;
}

void selectionSort(string arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}
		swapStr(&arr[minIndex], &arr[i]);
	}
}

void swapStr(string * first, string * second)
{
	string temp = *first;
	*first = *second;
	*second = temp;
}
