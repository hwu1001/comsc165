#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "HeartsHelper.h"

///<summary> 
///Player class used to represent a player in a game of Hearts.
///</summary>
class Player
{
public:
	Player();
	~Player();
	// Round hand functions
	std::vector<Card> getRoundHand();
	void setRoundHand(std::vector<Card> &hand);
	void addCardsToRoundHand(std::vector<Card> &cards);
	void removeCardInRoundHand(Card &card);
	void removeCardsInRoundHand(std::vector<Card> &cards);
	void clearRoundHand();
	// Points total functions
	int getPointsTotal();
	void addToPointsTotal(int val);
	void addToAllPoints(int val);
	void subtractFromPointsTotal(int val);
	// Points this found functions
	int getPointsThisRound();
	void clearPointsThisRound();
	// Points this trick functions
	int getPointsThisTrick();
	void clearPointsThisTrick();
	

private:
	std::vector<Card> m_roundHand;
	int m_pointsTotal;
	int m_pointsThisRound;
	int m_pointsThisTrick;
};

///<summary> 
/// Constructor for Player object.
///</summary>
///<returns> Nothing. </returns>
Player::Player()
{
	m_pointsTotal = 0;
	m_pointsThisRound = 0;
}

///<summary> Default destructor for Player class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Player::~Player()
{
}

///<summary> Getter function for round hand. </summary>
///<returns> The hand of the player for a particular round, in the form of a vector of Cards. </returns>
inline std::vector<Card> Player::getRoundHand()
{
	return m_roundHand;
}

///<summary> Getter function for player's total points. </summary>
///<returns> Player's total points. </returns>
inline int Player::getPointsTotal()
{
	return m_pointsTotal;
}

///<summary> Setter function for round hand and sorts the hand. </summary>
///<param name="hand"> Vector of cards representing hand. </param>
///<returns> Nothing. </returns>
inline void Player::setRoundHand(std::vector<Card> &hand)
{
	m_roundHand = hand;
	Deck::sort(m_roundHand);
}

///<summary> Appends a given vector of cards to the round hand and sorts the hand. </summary>
///<param name="cards"> Vector of cards to be appended. </param>
///<returns> Nothing. </returns>
inline void Player::addCardsToRoundHand(std::vector<Card>& cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		m_roundHand.push_back(cards.at(i));
	}
	Deck::sort(m_roundHand);
}

///<summary> Removes a single card from the round hand. </summary>
///<param name="card"> Card to be removed from round hand. </param>
///<returns> Nothing. </returns>
inline void Player::removeCardInRoundHand(Card &card)
{
	Deck::removeCard(m_roundHand, card);
}

///<summary> Removes a set of cards in a given vector from the round hand. </summary>
///<param name="cards"> Vector of cards to be removed. </param>
///<returns> Nothing. </returns>
inline void Player::removeCardsInRoundHand(std::vector<Card>& cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		Deck::removeCard(m_roundHand, cards.at(i));
	}
}

///<summary> Adds a value to the player's total points in the game. </summary>
///<param name="val"> The number to add to the player's points total. </param>
///<returns> Nothing. </returns>
inline void Player::addToPointsTotal(int val)
{
	m_pointsTotal = m_pointsTotal + val;
}

///<summary> Adds a value to the player's total points, points this round, and points this trick. </summary>
///<param name="val"> The number to be added to the player's points. </param>
///<returns> Nothing. </returns>
inline void Player::addToAllPoints(int val)
{
	m_pointsTotal = m_pointsTotal + val;
	m_pointsThisRound = m_pointsThisRound + val;
	m_pointsThisTrick = m_pointsThisTrick + val;
}

///<summary> Subtracts a value from the player's total points. </summary>
///<param name="val"> The number to subtract from the player's total points. </param>
///<returns> Nothing. </returns>
inline void Player::subtractFromPointsTotal(int val)
{
	m_pointsTotal = m_pointsTotal - val;
}

///<summary> Getter for the player's points this round. </summary>
///<returns> Player's points this round. </returns>
inline int Player::getPointsThisRound()
{
	return m_pointsThisRound;
}

///<summary> Sets a player's points for the round to zero. </summary>
///<returns> Nothing. </returns>
inline void Player::clearPointsThisRound()
{
	m_pointsThisRound = 0;
}

///<summary> Getter for the player's points this trick. </summary>
///<returns> Player's points this trick. </returns>
inline int Player::getPointsThisTrick()
{
	return m_pointsThisTrick;
}

///<summary> Set's the player's points this trick to zero. </summary>
///<returns> Nothing. </returns>
void Player::clearPointsThisTrick()
{
	m_pointsThisTrick = 0;
}

///<summary> Removes all cards from the player's round hand. </summary>
///<returns> Nothing. </returns>
inline void Player::clearRoundHand()
{
	m_roundHand.clear();
}
#endif // !PLAYER_H
