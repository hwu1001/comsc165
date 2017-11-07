// Henry Wu
// COMSC 165
// Section 3015
// Homework 5

#include <iostream>
#include "Card.h"
#include "Deck.h"

using namespace std;

int main()
{
	int choice;
	Deck deck;
	bool newShuffle = true;
	vector<vector<Card>> handCollection;

	do
	{
		const int SELECT_MIN = 1, SELECT_MAX = 3;
		choice = 0;
		cout << "Deck Program" << '\n';
		cout << "1. Shuffle Deck" << '\n';
		cout << "2. Deal Cards" << '\n';
		cout << "3. Sort Cards" << '\n';
		cout << "What would you like to do? (q to quit) ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			deck.shuffle();
			newShuffle = true;
			cout << "Deck shuffled." << '\n';
			break;
		case 2:
			if (handCollection.empty() || newShuffle)
			{
				handCollection = deck.deal(4, 13);
			}
			Deck::display(handCollection);
			newShuffle = false;
			break;
		case 3:
			if (handCollection.empty())
			{
				cout << "No cards dealt, cannot sort." << endl;
			}
			else
			{
				for (int i = 0; i < handCollection.size(); i++)
				{
					Deck::sort(handCollection.at(i));
				}
				Deck::display(handCollection);
			}
		default:
			if ((choice > SELECT_MAX || choice < SELECT_MIN) && !cin.fail())
			{
				cout << "Invalid selection, please enter again" << endl;
			}
			break;
		}
	} while (!cin.fail());
	return 0;
}
