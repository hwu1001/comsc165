// Programming challenge 5-13

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int numGuesses = 0, randomNum, guess, MAX = 100;
	//unsigned seed;

	//seed = time(0);
	srand(time(0));
	randomNum = rand() % MAX + 1;

	do
	{
		cout << "Guess the random number: ";
		cin >> guess;
		numGuesses++;

		if (guess > randomNum)
		{
			cout << "Too high, try again" << endl;
		}
		else if (guess < randomNum)
		{
			cout << "Too low, try again" << endl;
		}
		else
		{
			cout << "Congratulations! You figured out my number in " << numGuesses << " tries" << endl;
		}

	} while (guess != randomNum);

	return 0;
}