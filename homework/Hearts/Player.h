#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <algorithm> // needed for std::includes()
#include "Card.h"
#include "Deck.h"

class Player
{
public:
	Player();
	~Player();
	std::vector<Card> getRoundHand();
	int getPoints();
	std::vector<Card> getCardsFromWonTricks();
	void setRoundHand(std::vector<Card> &hand);
	void addToPoints(int val);
	void addToCardsFromWonTricks(Card card);
	void clearCardsFromWonTricks();
	bool hasShotTheMoon();

private:
	std::vector<Card> m_roundHand;
	int m_points;
	std::vector<Card> m_cardsFromWonTricks;
	static std::vector<Card> m_shotTheMoonCards;
};

Player::Player()
{
}

Player::~Player()
{
}
inline std::vector<Card> Player::getRoundHand()
{
	return m_roundHand;
}
inline int Player::getPoints()
{
	return m_points;
}
inline std::vector<Card> Player::getCardsFromWonTricks()
{
	return m_cardsFromWonTricks;
}
inline void Player::setRoundHand(std::vector<Card> &hand)
{
	m_roundHand = hand;
}
inline void Player::addToPoints(int val)
{
	m_points = m_points + val;
}
inline void Player::addToCardsFromWonTricks(Card card)
{
	m_cardsFromWonTricks.push_back(card);
}
inline void Player::clearCardsFromWonTricks()
{
	m_cardsFromWonTricks.clear();
}
inline bool Player::hasShotTheMoon()
{
	Deck::sort(m_cardsFromWonTricks);
	// m_shootTheMoonCards is already sorted
	return std::includes(m_cardsFromWonTricks.begin(), m_cardsFromWonTricks.end(), m_shotTheMoonCards.begin(), m_shotTheMoonCards.end()) ;
}

std::vector<Card> m_shotTheMoonCards =
{
	Card(0, Card::Suit::HEARTS),
	Card(1, Card::Suit::HEARTS),
	Card(2, Card::Suit::HEARTS),
	Card(3, Card::Suit::HEARTS),
	Card(4, Card::Suit::HEARTS),
	Card(5, Card::Suit::HEARTS),
	Card(6, Card::Suit::HEARTS),
	Card(7, Card::Suit::HEARTS),
	Card(8, Card::Suit::HEARTS),
	Card(9, Card::Suit::HEARTS),
	Card(10, Card::Suit::HEARTS),
	Card(11, Card::Suit::HEARTS),
	Card(12, Card::Suit::HEARTS),
	Card(10, Card::Suit::SPADES) // Queen of Spades
};
#endif // !PLAYER_H

