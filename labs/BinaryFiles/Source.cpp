#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> // for iter_swap()
#include <cstdlib> // for srand() and rand()
#include <ctime> // for time()
#include "Card.h"

using namespace std;

void initializeDeck(vector<Card> &deck);
void storeDeck(vector<Card> &deck, fstream &ioFile);
void loadDeck(vector<Card> &deck, fstream &ioFile);
void shuffleDeck(vector<Card> &deck);

int main()
{

	fstream ioFile;
	vector<Card> deck;

	ioFile.open("deck.txt", ios::out | ios::binary);

	if (ioFile)
	{
		initializeDeck(deck);
		storeDeck(deck, ioFile);

		// To prove the collection is repopulated
		deck.clear();
		deck.resize(52);
		
		ioFile.close();
		ioFile.clear();
		ioFile.open("deck.txt", ios::in | ios::binary);
		loadDeck(deck, ioFile);
		shuffleDeck(deck);

		for (Card &card : deck)
		{
			cout << card.getDescription() + '\n';
		}
	}
	else
	{
		cout << "Error opening file." << endl;
	}

	ioFile.close();
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

void storeDeck(vector<Card> &deck, fstream &ioFile)
{
	for (Card &card : deck)
	{
		int num = card.getNumber();
		int suit = static_cast<int>(card.getSuit());
		ioFile.write(reinterpret_cast<char*>(&num), sizeof(num));
		ioFile.write(reinterpret_cast<char*>(&suit), sizeof(suit));

		int descLen = card.getDescription().length();
		ioFile.write(reinterpret_cast<char*>(&descLen), sizeof(descLen));
		ioFile.write(card.getDescription().data(), descLen);
	}
	
}

void loadDeck(vector<Card> &deck, fstream &ioFile)
{
	char buffer[256];
	int num, suit, descLen;
	string desc;
	for (int i = 0; i < 52; i++)
	{
		ioFile.read(reinterpret_cast<char*>(&num), sizeof(num));
		ioFile.read(reinterpret_cast<char*>(&suit), sizeof(suit));
		ioFile.read(reinterpret_cast<char*>(&descLen), sizeof(descLen));
		
		// I'm only reading this because the lab says we have to, it's not actually needed
		ioFile.read(buffer, descLen);
		buffer[descLen] = '\0';
		desc = buffer;

		deck.at(i) = Card(num, static_cast<Card::Suit>(suit), desc);
	}
}

void shuffleDeck(vector<Card> &deck)
{
	srand(time(0));
	int random;
	// Could use std::random_shuffle, but we can implement Fisher-Yates shuffle
	for (int i = deck.size() - 1; i > 0; i--)
	{
		random = rand() % 52;
		iter_swap(deck.begin() + i, deck.begin() + random);
	}
}
