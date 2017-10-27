#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:
	enum class Suit
	{
		DIAMONDS,
		CLUBS,
		HEARTS,
		SPADES
	};
	Card();
	Card(int num, Card::Suit suit);
	Card(int num, Card::Suit suit, std::string desc);
	~Card();
	Card::Suit getSuit();
	int getNumber();
	std::string getDescription();
	std::string* getSuitStrings();
	std::string* getNumStrings();

private:
	Card::Suit m_suit;
	int m_number;
	std::string m_description;
	static std::string m_suitStrings[];
	static std::string m_numStrings[];

};

Card::Card()
{
}

Card::Card(int num, Card::Suit suit)
{
	m_number = num;
	m_suit = suit;
	m_description = Card::m_numStrings[num] + " of " + Card::m_suitStrings[static_cast<int>(suit)];
}

Card::Card(int num, Card::Suit suit, std::string desc)
{
	// Make this constructor just for when we read all the data back and repopulate the collection
	m_number = num;
	m_suit = suit;
	m_description = desc;
}

Card::~Card()
{
}

inline Card::Suit Card::getSuit()
{
	return m_suit;
}

inline int Card::getNumber()
{
	return m_number;
}

inline std::string Card::getDescription()
{
	return m_description;
}

inline std::string * Card::getSuitStrings()
{
	return Card::m_suitStrings;
}

inline std::string * Card::getNumStrings()
{
	return Card::m_numStrings;
}


std::string Card::m_suitStrings[] = { "Diamonds", "Clubs", "Hearts", "Spades" };
std::string Card::m_numStrings[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

#endif // !CARD_H

