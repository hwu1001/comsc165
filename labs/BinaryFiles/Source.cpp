#include <iostream>
#include <vector>
#include <fstream>
#include "Card.h"

using namespace std;

void initializeDeck(vector<Card> &deck);

int main()
{
	
	fstream ioFile("deck.txt", ios::binary);
	vector<Card> deck;

	initializeDeck(deck);



	return 0;
}

void initializeDeck(vector<Card> &deck)
{
	for (int i = 0; i < 4; i++)
	{
		Card::Suit suit = static_cast<Card::Suit>(i);
		for (int j = 0; j < 13; j++)
		{
			deck.push_back(Card(j, suit));
		}
	}
}
