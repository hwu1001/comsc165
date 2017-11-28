#ifndef HEARTSGAME_H
#define HEARTSGAME_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm> // needed for std::includes()
#include <string>
#include <Windows.h>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "InvalidCardPlayed.h"

///<summary> 
///Class that holds necessary variables and functions to allow user to play a game of Hearts.
///Supports 3, 4, or 5 players.
///</summary>
class HeartsGame
{
public:
	HeartsGame();
	HeartsGame(int numPlayers);
	~HeartsGame();
	void start();
	static bool isValidNumberOfPlayers(int numPlayers);
	

private:
	std::vector<Player> m_players;
	Deck m_deck;
	int m_handSize;
	Card m_startingCard;
	Card::Suit m_leadingCardSuit;
	bool m_canPlayHearts;

	int findStartingRoundPlayerPos();
	void initializePlayerHands();
	void passCards();
	int tallyPoints(std::vector<Card> &cards);
	bool isValidCardPlay(Card &card, int playerIndex, bool canLeadQofS, bool isFirstTrickOfGame, bool isLeadingCard);
	void initializePlayerOrder(std::vector<int> &playerOrder, bool isFirstTrickOfGame, int largestCardPosition);
	void playTrick(std::vector<int> playerOrder, std::vector<Card> &trickCards, bool isFirstTrickOfGame);
	void setLeadingCardSuit(Card::Suit suit);
	void setCanPlayHearts(int playerIndex, bool isLeadingCard);
	void handleShootTheMoon();
	void endRound();
	bool isDuplicatePassedCard(std::vector<Card> &passedCards, std::string cardStr);
	void playRound();
	void display(std::string title);
	int findPosOfWinningCardInTrick(std::vector<Card> &trickCards);
	
};

///<summary> Default constructor for HeartsGame. If used it assumes only 4 players. By default doesn't support 3 or 5. </summary>
///<returns> Nothing. </returns>
HeartsGame::HeartsGame()
{
	m_startingCard.setNumAndSuit(0, Card::Suit::CLUBS);
	m_handSize = 13;
}

///<summary> Constructor for HeartsGame object that sets up the deck for the given number of players. </summary>
///<param name="numPlayers"> Number of players in the game. </param>
///<returns> Nothing. </returns>
inline HeartsGame::HeartsGame(int numPlayers)
{
	m_players.resize(numPlayers);
	m_canPlayHearts = false;
	if (numPlayers == 3)
	{
		m_startingCard.setNumAndSuit(0, Card::Suit::CLUBS);
		Card card(0, Card::Suit::DIAMONDS);
		m_deck.removeOneDeckCard(card);
		m_handSize = 17;
	}
	else if (numPlayers == 5)
	{
		m_startingCard.setNumAndSuit(1, Card::Suit::CLUBS);
		Card card1(0, Card::Suit::DIAMONDS);
		Card card2(0, Card::Suit::CLUBS);
		m_deck.removeOneDeckCard(card1);
		m_deck.removeOneDeckCard(card2);
		m_handSize = 10;
	}
	else
	{
		m_startingCard.setNumAndSuit(0, Card::Suit::CLUBS);
		m_handSize = 13;
	}
}

///<summary> Default destructor for HeartsGame. No special actions taken. </summary>
///<returns> Nothing. </returns>
HeartsGame::~HeartsGame()
{
}

///<summary> Starts a game of Hearts. </summary>
///<returns> Nothing. </returns>
void HeartsGame::start()
{
	bool keepPlaying = true;
	char choice;
	do
	{
		HeartsGame::playRound();
		HeartsGame::display("End Of Round");

		std::cout << "Continue playing? (Y/N) ";
		std::cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			keepPlaying = true;
		}
		else
		{
			keepPlaying = false;
		}
	} while (keepPlaying);

}

///<summary> Plays a single round of Hearts. Meaning the entire deck is dealt and the round only ends when all players are out of cards. </summary>
///<returns> Nothing. </returns>
void HeartsGame::playRound()
{
	bool isFirstTrickOfGame = true;
	std::vector<int> playerOrder;
	std::vector<Card> trickCards;
	int nextLeadingPlayerPosition = -1;
	std::string titleText;

	std::cin.ignore();
	HeartsGame::initializePlayerHands();
	HeartsGame::passCards();

	// Keep playing until players run out of cards. Need to initialize player order first, then play the trick
	while (m_players.at(0).getRoundHand().size() > 0)
	{
		HeartsGame::initializePlayerOrder(playerOrder, isFirstTrickOfGame, nextLeadingPlayerPosition);
		if (isFirstTrickOfGame)
		{
			titleText = "Playing Round - Must begin with: " + m_startingCard.getDescription();
		}
		else
		{
			titleText = "Playing Round";
		}
		HeartsGame::display(titleText);
		HeartsGame::playTrick(playerOrder, trickCards, isFirstTrickOfGame);

		// Determine who won the trick so they can lead next trick and determine if points need to be allocated
		int largestCardPos = HeartsGame::findPosOfWinningCardInTrick(trickCards);
		nextLeadingPlayerPosition = playerOrder.at(largestCardPos);
		m_players.at(nextLeadingPlayerPosition).addToAllPoints(HeartsGame::tallyPoints(trickCards));
		if (isFirstTrickOfGame)
		{
			isFirstTrickOfGame = false;
		}
		playerOrder.clear();
		trickCards.clear();
	}
	// Handle the end of the round
	HeartsGame::handleShootTheMoon();
	HeartsGame::endRound();
}

///<summary>
///Display player's points and hands of cards on the console.
///</summary>
///<param name="title"> Title to go with the player's cards to denote which part of the game is happening. </param>
///<returns> Nothing. </returns>
void HeartsGame::display(std::string title)
{
	system("cls");
	int numPlayers = m_players.size();
	int handSize = m_players.at(0).getRoundHand().size(); // all hand sizes are the same
	std::string tempStr;

	if (!title.empty())
	{
		std::cout << title << '\n';
	}
	std::cout << std::left;
	for (int i = 0; i < numPlayers; i++)
	{
		tempStr = "Player " + std::to_string(i + 1);
		std::cout << std::setw(15) << tempStr;
	}
	std::cout << '\n';
	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << std::setw(15) << "==========";
	}
	std::cout << '\n';
	for (size_t i = 0; i < numPlayers; i++)
	{
		std::string ptsStr = "Points: " + std::to_string(m_players.at(i).getPointsTotal());
		std::cout << std::setw(15) << ptsStr;
	}
	std::cout << '\n';
	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << std::setw(15) << "==========";
	}
	std::cout << '\n';
	for (int i = 0; i < handSize; i++)
	{
		for (int j = 0; j < numPlayers; j++)
		{
			std::cout << std::setw(15) << std::left << m_players.at(j).getRoundHand().at(i).getDescription();
		}
		std::cout << '\n';
	}
}

///<summary> Determines whether the number of players is valid for a game of Hearts. </summary>
///<param name="numPlayers"> Number of players in the game. </param>
///<returns> True if the number of players is 3, 4, or 5, otherwise false. </returns>
inline bool HeartsGame::isValidNumberOfPlayers(int numPlayers)
{
	if (numPlayers >= 3 && numPlayers <= 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///<summary> 
///Finds the position of the player with the starting card in their round hand at the beginning of a round. 
///3 players - Staring card is 2 of Clubs
///4 players - Starting card is 2 of Clubs
///5 players - Starting card is 3 of Clubs
///</summary>
///<returns> The numeric position in the vector holding the players telling which player has the starting card in their hand.. </returns>
int HeartsGame::findStartingRoundPlayerPos()
{
	int pos = 0;
	for (size_t i = 0; i < m_players.size(); i++)
	{
		pos = Deck::findPositionOfCard(m_players.at(i).getRoundHand(), m_startingCard);
		if (pos != -1)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

///<summary> Used at the beginning of each round to shuffle the deck and deal players their round hands. </summary>
///<returns> Nothing. </returns>
void HeartsGame::initializePlayerHands()
{
	m_deck.shuffle();
	std::vector<std::vector<Card>> handCollection = m_deck.deal(m_players.size(), m_handSize);
	for (int i = 0; i < m_players.size(); i++)
	{
		m_players.at(i).setRoundHand(handCollection.at(i));
	}
}

///<summary> 
///Handles the card passing phase that begins at the start of each round where each player selects 3 cards to pass to the player to their right. 
///E.g., player 1 selects 3 cards and passes to player 2, etc.
///Last player passes to the first player
///</summary>
///<returns> Nothing. </returns>
void HeartsGame::passCards()
{
	std::vector<std::vector<Card>> passedCards;
	std::string cardStr;
	int numPlayers = m_players.size();
	// For each player ask them to select 3 cards to pass
	passedCards.resize(numPlayers);
	for (size_t i = 0; i < numPlayers; i++)
	{
		system("cls");
		// Display all cards
		HeartsGame::display("Passing Cards");
		std::cout << '\n';
		std::cout << "Player " << i + 1 << '\n';
		// Select the 3 cards for one player
		for (size_t j = 0; j < 3; j++)
		{
			cardStr = "";
			bool valid = false;
			do
			{
				std::cout << "Enter card to pass: ";
				std::getline(std::cin, cardStr);
				try
				{
					if (!Deck::isCardStringValid(cardStr))
					{
						throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::NONEXISTENT_CARD);
					}
					if (!Deck::isCardInCollection(m_players.at(i).getRoundHand(), cardStr))
					{
						throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::CARD_IN_HAND);
					}
					if (HeartsGame::isDuplicatePassedCard(passedCards.at(i), cardStr))
					{
						throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::DUPLICATE_CARD);
					}
					valid = true;
					passedCards.at(i).push_back(Deck::convertCardStrToCard(cardStr));
				}
				catch (InvalidCardPlayed &icp)
				{
					std::cout << icp.getErrorDescription() << '\n';
					valid = false;
				}
			} while (!valid);

		}
	}
	// Once all cards are selected, remove them from appropriate owner
	for (size_t i = 0; i < numPlayers; i++)
	{
		int swapPlayer;
		// The last player passes their cards to the first player
		if (i == numPlayers - 1)
		{
			swapPlayer = 0;
		}
		else
		{
			swapPlayer = i + 1;
		}
		m_players.at(i).removeCardsInRoundHand(passedCards.at(i));
		m_players.at(swapPlayer).addCardsToRoundHand(passedCards.at(i));
	}
}

///<summary> 
///Takes the cards contributed during a trick and determines how many points are in the cards. 
///Note that all Hearts are worth 1 point and the Queen of Spades is worth 13 points.
///</summary>
///<returns> The number of points available in the collection of cards. </returns>
int HeartsGame::tallyPoints(std::vector<Card> &cards)
{
	int points = 0;
	for (Card &card : cards)
	{
		if (card.getSuit() == Card::Suit::HEARTS)
		{
			points++;
		}
		else if (card == Card(10, Card::Suit::SPADES)) // Queen of Spades
		{
			points = points + 13;
		}
	}
	return points;
}

///<summary> 
///Determines whether a given card played during a trick is valid or not. 
///</summary>
///<param name="card"> The card played. </param>
///<param name="playerIndex"> Index of the player in m_players who is playing a card. </param>
///<param name="canLeadQofS"> Whether the player can lead with the Queen of Spades or not. </param>
///<param name="isFirstTrickOfGame"> Whether this is the first trick of the game or not. </param>
///<param name="isLeadingCard"> Whether the card being played is the leading card of the trick or not. </param>
///<returns> True if the card is valid to play during the trick, otherwise false. </returns>
bool HeartsGame::isValidCardPlay(Card &card, int playerIndex, bool canLeadQofS, bool isFirstTrickOfGame, bool isLeadingCard)
{
	bool result;
	if (card.getSuit() == Card::Suit::HEARTS)
	{
		HeartsGame::setCanPlayHearts(playerIndex, isLeadingCard);
	}
	
	try
	{
		if (!Deck::isCardInCollection(m_players.at(playerIndex).getRoundHand(), card))
		{
			throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::CARD_IN_HAND);
		}
		else if (isFirstTrickOfGame && isLeadingCard && card != m_startingCard)
		{
			throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::BAD_LEADING_CARD);
		}
		else if (!canLeadQofS && card == Card(10, Card::Suit::SPADES))
		{
			throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::CAN_LEAD_QUEEN_OF_SPADES);
		}
		else if (!m_canPlayHearts && card.getSuit() == Card::Suit::HEARTS)
		{
			throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::CAN_HEARTS_BE_PLAYED);
		}
		else if (!isLeadingCard && card.getSuit() != m_leadingCardSuit && Deck::hasOneCardOfSuitType(m_players.at(playerIndex).getRoundHand(), m_leadingCardSuit))
		{
			throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::NOT_SAME_SUIT);
		}
		result = true;
	}
	catch (InvalidCardPlayed &icp)
	{
		std::cout << icp.getErrorDescription() << '\n';
		result = false;
	}
	return result;
}

///<summary> 
///Finds the position of the winning card for a given trick.
///Note that the winning card must be of the same suit as the leading card
///</summary>
///<param name="trickCards"> The vector of cards played during a given trick. </param>
///<returns> The position of the winning card in the given trick cards. </returns>
int HeartsGame::findPosOfWinningCardInTrick(std::vector<Card> &trickCards)
{
	int pos = 0;
	std::vector<Card> cardsOfLeadingSuit;
	for (size_t i = 0; i < trickCards.size() - 1; i++)
	{
		// Cards that don't start with the leading suit cannot win a trick
		if (trickCards.at(i + 1).getSuit() == m_leadingCardSuit && trickCards.at(pos) < trickCards.at(i + 1))
		{
			pos = i + 1;
		}
	}
	return pos;
}

///<summary> 
///Determines the player order for each trick played.
///For the first trick of the game the leading player is the one with the leading card.
///For each subsequent trick after the first the leading player is the one who "won" the last trick
///NOTE: Player's trick points are cleared in this function for each trick after the first one is played so the next player order can be determined.
///</summary>
///<param name="playerOrder"> Vector to be filled with the order in which players go for this trick. </param>
///<param name="isFirstTrickOfGame"> Whether or not it is the first trick of the game. </param>
///<param name="leadingPlayerPosition"> The position of the player that won the previous trick. Only needed after the first round of the game.</param>
///<returns> Return is done in the playerOrder variable. </returns>
void HeartsGame::initializePlayerOrder(std::vector<int> &playerOrder, bool isFirstTrickOfGame, int leadingPlayerPosition)
{
	int leadPosition;
	if (isFirstTrickOfGame)
	{
		leadPosition = HeartsGame::findStartingRoundPlayerPos();
	}
	else
	{
		leadPosition = leadingPlayerPosition;
	}
	
	playerOrder.push_back(leadPosition);
	for (int i = leadPosition + 1; i < m_players.size(); i++)
	{
		playerOrder.push_back(i);
	}
	for (int i = 0; i < leadPosition; i++)
	{
		playerOrder.push_back(i);
	}
	// Need to clear trick points after determining the order so they can start fresh for the new trick
	if (!isFirstTrickOfGame)
	{
		for (size_t i = 0; i < m_players.size(); i++)
		{
			m_players.at(i).clearPointsThisTrick();
		}
	}
}

///<summary> 
///Plays one trick in Hearts.
///A trick is finished after each player in the game has contributed one card to play.
///</summary>
///<param name="playerOrder"> Vector to be filled with the order in which players go for this trick. </param>
///<param name="trickCards"> Output to let the round handler know which cards were played this trick. </param>
///<param name="isFirstTrickOfGame"> Whether or not it is the first trick of the game. </param>
///<returns> Nothing. </returns>
void HeartsGame::playTrick(std::vector<int> playerOrder, std::vector<Card> &trickCards, bool isFirstTrickOfGame)
{
	bool canLeadQofS = true;
	for (int i = 0; i < m_players.size(); i++)
	{
		std::string cardStr;
		bool validCardPlay = false;
		Card playedCard;
		if (isFirstTrickOfGame && i == 0 && !Deck::hasOneCardOfSuitType(m_players.at(playerOrder.at(i)).getRoundHand(), Card::Suit::CLUBS))
		{
			canLeadQofS = false;
		}
		do
		{
			std::cout << "Player " << playerOrder.at(i) + 1 << '\n';
			std::cout << "Enter a card: ";
			std::getline(std::cin, cardStr);
			try
			{
				if (!Deck::isCardStringValid(cardStr))
				{
					throw InvalidCardPlayed(InvalidCardPlayed::ExceptionType::NONEXISTENT_CARD);
				}
				playedCard = Deck::convertCardStrToCard(cardStr);
 
				if (!HeartsGame::isValidCardPlay(playedCard, playerOrder.at(i), canLeadQofS, isFirstTrickOfGame, i == 0))
				{
					validCardPlay = false;
				}
				else
				{
					validCardPlay = true;
					if (i == 0)
					{
						HeartsGame::setLeadingCardSuit(playedCard.getSuit());
					}
				}
			}
			catch (InvalidCardPlayed &icp)
			{
				validCardPlay = false;
				std::cout << icp.getErrorDescription() << '\n';
			}

		} while (!validCardPlay);

		trickCards.push_back(playedCard);
		m_players.at(playerOrder.at(i)).removeCardInRoundHand(playedCard);
	}
}

///<summary> 
///Sets the leading card suit for the game. Changes each trick.
///</summary>
///<param name="suit"> The suit of the leading card for a given trick. </param>
///<returns> Nothing. </returns>
void HeartsGame::setLeadingCardSuit(Card::Suit suit)
{
	m_leadingCardSuit = suit;
}

///<summary> 
///Sets the game variable for whether players can play Hearts in a given round. It does so by determing whether a player can play a Heart card in a given trick.
///Hearts can only be played when a player that is not leading plays a Heart where the leading card is a different suit. 
///(i.e., the non-leading player does not have any cards of the leading suit left)
///</summary>
///<param name="playerIndex"> Index of the player playing their card this trick. </param>
///<param name="isLeadingCard"> Whether or not the card being played is the leading one. </param>
///<returns> Nothing. </returns>
void HeartsGame::setCanPlayHearts(int playerIndex, bool isLeadingCard)
{
	if (!isLeadingCard && !Deck::hasOneCardOfSuitType(m_players.at(playerIndex).getRoundHand(), m_leadingCardSuit))
	{
		m_canPlayHearts = true;
	}
}

///<summary> 
///Handles the shooting the moon scenario at the end of each round.
///"Shooting the moon" only happens when a player that round wins all Hearts cards and the Queen of Spades. 
///If this is true then the player that "shoots the moon" receives zero points and all other players get 26 points.
///</summary>
///<returns> Nothing. </returns>
void HeartsGame::handleShootTheMoon()
{
	int position = -1;
	for (size_t i = 0; i < m_players.size(); i++)
	{
		// If you have 26 points it means the player has all Hearts (13 pts) and the Queen of Spades (13 pts) a.k.a. "Shooting the moon"
		if (m_players.at(i).getPointsThisRound() == 26)
		{
			position = i;
			break;
		}
	}
	if (position != -1)
	{
		for (size_t i = 0; i < m_players.size(); i++)
		{
			if (i == position)
			{
				// Player that shoots the moon gets zero points this turn
				m_players.at(position).subtractFromPointsTotal(m_players.at(position).getPointsThisRound());
			}
			else
			{
				m_players.at(i).subtractFromPointsTotal(m_players.at(i).getPointsThisRound());
				m_players.at(i).addToPointsTotal(26);
			}
		}
	}
}

///<summary> 
///Cleans up player variables for the end of the round so that Player objects will be ready for the next round.
///</summary>
///<returns> Nothing. </returns>
void HeartsGame::endRound()
{
	for (size_t i = 0; i < m_players.size(); i++)
	{
		m_players.at(i).clearPointsThisRound();
		m_players.at(i).clearPointsThisTrick();
		m_players.at(i).clearRoundHand();
	}
	m_canPlayHearts = false;
}

///<summary> 
///Determines whether a given card has been selected previously.
///</summary>
///<param name="passedCards"> The vector of cards already selected for passing. </param>
///<param name="cardStr"> A string representing the Card object that is being selected. </param>
///<returns> True if card selected has been selected previously, otherwise false. </returns>
bool HeartsGame::isDuplicatePassedCard(std::vector<Card> &passedCards, std::string cardStr)
{
	Card chosenCard = Deck::convertCardStrToCard(cardStr);
	std::vector<Card>::iterator it = std::find(passedCards.begin(), passedCards.end(), chosenCard);
	return (it != passedCards.end());
}

#endif // !HEARTSGAME_H

