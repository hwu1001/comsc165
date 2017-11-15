#include <iostream>
#include <vector>

using namespace std;

template <class T>
void rotate(T array[], int size);

template <class T>
void display(T array[], int size);

template <class T>
void rotate(vector<T> &collection);

template <class T>
void display(vector<T> &collection);

int main()
{
	int nums[] = { 1, 3, 5, 7 };
	char chars[] = {'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i < 4; i++)
	{
		display(nums, 4);
		rotate(nums, 4);
	}
	cout << '\n';
	for (int i = 0; i < 5; i++)
	{
		display(chars, 5);
		rotate(chars, 5);
	}

	//vector<int> vecNums = { 1, 3, 5, 7 };
	//vector<char> vecChar = { 'a', 'b', 'c', 'd', 'e' };
	//for (int i = 0; i < vecNums.size(); i++)
	//{
	//	display(vecNums);
	//	rotate(vecNums);
	//}
	//cout << '\n';
	//for (int i = 0; i < vecChar.size(); i++)
	//{
	//	display(vecChar);
	//	rotate(vecChar);
	//}
	
	return 0;
}

template<class T>
void rotate(T array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		T temp = array[i];
		array[i] = array[i + 1];
		array[i + 1] = temp;
	}
}

template<class T>
void display(T array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << '\n';
}

template<class T>
void rotate(vector<T> &collection)
{
	for (int i = 0; i < collection.size() - 1; i++)
	{
		T temp = collection.at(i);
		collection.at(i) = collection.at(i + 1);
		collection.at(i + 1) = temp;
	}
}

template<class T>
void display(vector<T> &collection)
{
	for (int i = 0; i < collection.size(); i++)
	{
		cout << collection.at(i) << " ";
	}
	cout << '\n';
}

