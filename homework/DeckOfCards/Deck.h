#ifndef DECK_H
#define DECK_H
#include <vector>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	void initialize();
	void shuffle();

private:
	std::vector<Card> m_cards;

};

Deck::Deck()
{
}

Deck::~Deck()
{
}

void Deck::initialize()
{
}

void Deck::shuffle()
{
}

#endif // !DECK_H

