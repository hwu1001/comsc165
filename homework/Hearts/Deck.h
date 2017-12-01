#ifndef DECK_H
#define DECK_H
#include <vector>
#include <cstdlib>   // for srand() and rand()
#include <algorithm> // for iter_swap() and min()
#include <ctime>     // for time()
#include <Windows.h>
#include <iomanip>
#include "Card.h"

///<summary> 
///Deck class that holds Card objects. After creating a Deck object, it will be initialized as a 52 card deck with 4 suits (Clubs, Diamonds, Heart, Spades), 13 cards each 
///</summary>
class Deck
{
public:
	Deck();
	~Deck();
	void shuffle();
	std::vector<std::vector<Card>> deal(int numHands, int handSize);
	static void sort(std::vector<Card> &hand);
	void removeOneDeckCard(Card &card);

	// Static Functions
	static int findPositionOfCard(std::vector<Card> &cards, Card &card);
	static bool isCardStringValid(std::string cardStr);
	static bool isCardInCollection(std::vector<Card> &cards, Card &card);
	static bool isCardInCollection(std::vector<Card> &cards, std::string cardStr);
	static Card convertCardStrToCard(std::string cardStr);
	static void removeCard(std::vector<Card> &cards, Card &card);
	static bool hasOneCardOfSuitType(std::vector<Card> &cards, Card::Suit suit);

private:
	std::vector<Card> m_cards;
	void initialize();
	static void mergeSort(std::vector<Card> &hand);
	static void mergeCollection(std::vector<Card> &hand, int leftIndex, int midIndex, int rightIndex, std::vector<Card> &temp);
};

///<summary> Constructor for Deck object that sets up the cards in the deck. </summary>
///<returns> Nothing. </returns>
Deck::Deck()
{
	this->initialize();
}

///<summary> Default destructor for Deck class. No special actions taken. </summary>
///<returns> Nothing. </returns>
Deck::~Deck()
{
}

///<summary> Initialize the Deck object with 52 cards, 13 cards each with 4 suits. </summary>
///<returns> Nothing. </returns>
void Deck::initialize()
{
	for (int i = 0; i < 4; i++)
	{
		Card::Suit suit = static_cast<Card::Suit>(i);
		for (int j = 0; j < 13; j++)
		{
			m_cards.push_back(Card(j, suit));
		}
	}
}

///<summary> Shuffle the Deck object by using a Fisher-Yates shuffle. All cards moved to random position. </summary>
///<returns> Nothing. </returns>
void Deck::shuffle()
{
	int deckSize = m_cards.size();
	srand(time(0));
	int random;
	// Could use std::random_shuffle, but we can implement Fisher-Yates shuffle
	for (int i = deckSize - 1; i > 0; i--)
	{
		random = rand() % deckSize;
		iter_swap(m_cards.begin() + i, m_cards.begin() + random);
	}
}

///<summary>
///Deals hands of cards of a specified size.
///</summary>
///<param name="numHands"> Number of hands to be dealt. </param>
///<param name="handSize"> Size of each hand dealt. </param>
///<returns> A vector of vectors holding Card objects representing hands dealt. </returns>
std::vector<std::vector<Card>> Deck::deal(int numHands, int handSize)
{
	std::vector<std::vector<Card>> handsCollection(numHands);
	int deckCounter = 0;
	for (int i = 0; i < numHands; i++)
	{
		for (int j = 0; j < handSize; j++)
		{
			handsCollection.at(i).push_back(m_cards.at(deckCounter));
			deckCounter++;
		}
	}
	return handsCollection;
}

///<summary>
///Sorts a given hand of Card objects in order based on suit and card value.
///Suit priority from lowest to highest: Clubs, Diamonds, Hearts, Spades
///Card value priority from lowest to highest: 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace
///</summary>
///<param name="hand"> Collection of Card objects representing a single hand to be sorted. </param>
///<returns> Nothing. </returns>
inline void Deck::sort(std::vector<Card> &hand)
{
	//Merge sort
	mergeSort(hand);
}

///<summary>
///Removes a given Card object from the Deck
///</summary>
///<param name="card"> Card object to be removed from the deck. </param>
///<returns> Nothing. </returns>
inline void Deck::removeOneDeckCard(Card &card)
{
	Deck::removeCard(m_cards, card);
}

///<summary>
///Finds the position of a given card in a vector of cards.
///NOTE: Assumes the provided vector is sorted from least to greatest.
///</summary>
///<param name="cards"> Vector of cards to search through. NOTE: Assumes the provided vector is sorted from least to greatest.</param>
///<param name="card"> Card object to be found. </param>
///<returns> The integer position of the given card in the provided vector. </returns>
int Deck::findPositionOfCard(std::vector<Card>& cards, Card &card)
{
	// binary search
	int leftIndex = 0;
	int rightIndex = cards.size() - 1;
	int mid, position = -1;
	bool found = false;
	while (!found && leftIndex <= rightIndex)
	{
		mid = (leftIndex + rightIndex) / 2;
		if (cards.at(mid) == card)
		{
			found = true;
			position = mid;
		}
		else if (cards.at(mid) < card)
		{
			leftIndex = mid + 1;
		}
		else
		{
			rightIndex = mid - 1;
		}
	}
	return position;
}

///<summary>
///Determines whether a string representing a card object is valid or not.
/// String is 2 characters long where the first denotes the value of the card and the second denotes the suit.
/// 0-9, T, J, Q, K, A - valid for first character. C, D, H, S - valid for second character.
///</summary>
///<param name="cardStr"> String representing Card object. </param>
///<returns> True if string represents a valid Card, otherwise false. </returns>
bool Deck::isCardStringValid(std::string cardStr)
{
	bool result = true;
	if (cardStr.length() != 2 || cardStr.empty())
	{
		result = false;
	}
	else
	{
		char firstChar = toupper(cardStr.at(0));
		char secondChar = toupper(cardStr.at(1));
		// Note that char - '0' turns the char into an int. (E.g., '0' -> 0)
		if (isdigit(firstChar) && (cardStr.at(0) - '0' < 2 || cardStr.at(0) - '0' > 9))
		{
			result = false;
		}
		else if (!isdigit(firstChar) && firstChar != 'T' && firstChar != 'J' && firstChar != 'Q' && firstChar != 'K' && firstChar != 'A')
		{
			result = false;
		}
		else if (secondChar != 'C' && secondChar != 'D' && secondChar != 'H' && secondChar != 'S')
		{
			result = false;
		}
	}

	return result;
}

///<summary>
///Determines whether a specific card is present in a vector of cards.
///</summary>
///<param name="cards"> Vector of cards where one is removed. NOTE: Assumes vector is sorted from least to greatest. </param>
///<param name="card"> Card object to find. </param>
///<returns> True if the given card is present in the vector provided, otherwise false. </returns>
bool Deck::isCardInCollection(std::vector<Card> &cards, Card &card)
{
	if (Deck::findPositionOfCard(cards, card) != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///<summary>
///Determines whether a specific card is present in a vector of cards.
///</summary>
///<param name="cards"> Vector of cards where one is removed. NOTE: Assumes vector is sorted from least to greatest. </param>
///<param name="cardStr"> String representing Card object to find. </param>
///<returns> True if the given card is present in the vector provided, otherwise false. </returns>
bool Deck::isCardInCollection(std::vector<Card> &cards, std::string cardStr)
{
	return isCardInCollection(cards, Deck::convertCardStrToCard(cardStr));
}

///<summary>
///Converts a string to a Card object.
/// String is 2 characters long where the first denotes the value of the card and the second denotes the suit.
/// 0-9, T, J, Q, K, A - valid for first character. C, D, H, S - valid for second character.
///</summary>
///<param name="cardStr"> String representing Card object. </param>
///<returns> A Card object. </returns>
Card Deck::convertCardStrToCard(std::string cardStr)
{
	char firstChar = cardStr.at(0);
	char secondChar = cardStr.at(1);
	int num;
	Card::Suit suit;
	if (isdigit(firstChar))
	{
		num = firstChar - '0';
		num = num - 2; // Need to subtract two when we initialize Card object (e.g., 2 of Clubs is at position 0)
	}
	else
	{
		switch (firstChar)
		{
		case 't':
		case 'T':
			num = 8;
			break;
		case 'j':
		case 'J':
			num = 9;
			break;
		case 'q':
		case 'Q':
			num = 10;
			break;
		case 'k':
		case 'K':
			num = 11;
			break;
		case 'a':
		case 'A':
			num = 12;
			break;
		}
	}

	switch (secondChar)
	{
	case 'c':
	case 'C':
		suit = Card::Suit::CLUBS;
		break;
	case 'd':
	case 'D':
		suit = Card::Suit::DIAMONDS;
		break;
	case 'h':
	case 'H':
		suit = Card::Suit::HEARTS;
		break;
	case 's':
	case 'S':
		suit = Card::Suit::SPADES;
		break;
	default:
		break;
	}
	return Card(num, suit);
}

///<summary>
///Removes a given Card object from given vector of cards
///</summary>
///<param name="cards"> Vector of cards where one is removed. NOTE: Assumes vector is sorted from least to greatest. </param>
///<param name="card"> Card object to be removed from the vector. </param>
///<returns> Nothing. </returns>
inline void Deck::removeCard(std::vector<Card> &cards, Card &card)
{
	int pos = Deck::findPositionOfCard(cards, card);
	cards.erase(cards.begin() + pos);
}

///<summary>
///Determines whether the given vector of cards has at least one card with the given suit.
///</summary>
///<param name="cards"> Vector of cards to search through.</param>
///<param name="suit"> Suit of card to search for in vector. </param>
///<returns> True if the given vector has at least one card of the given suit, otherwise false. </returns>
inline bool Deck::hasOneCardOfSuitType(std::vector<Card>& cards, Card::Suit suit)
{
	bool result = false;
	for (Card &card : cards)
	{
		if (card.getSuit() == suit)
		{
			result = true;
			break;
		}
	}
	return result;
}

///<summary>
///Merge sort algorithm for a hand of cards. Sorts the hand from lowest to highest value.
///</summary>
///<param name="hand"> Collection of Card objects representing a single hand to be sorted. </param>
///<returns> Nothing. </returns>
void Deck::mergeSort(std::vector<Card> &hand)
{
	int n = hand.size();
	std::vector<Card> temp(n);
	// Width expands by 2 each iteration to use the bottom up approach to the merge sort algorithm
	for (int width = 1; width < n; width = 2 * width)
	{
		for (int i = 0; i < n; i += 2 * width)
		{
			int leftStart = i;
			// Very important to use min here, otherwise odd numbered collections cannot be sorted appropriately
			int mid = min(i + width, n); // min() from algorithm library
			int rightEnd = min(i + 2 * width, n);
			mergeCollection(hand, leftStart, mid, rightEnd, temp);
		}
		// Copy temporary vector back into our final copy
		for (int i = 0; i < n; i++)
		{
			hand.at(i) = temp.at(i);
		}
	}
}

///<summary>
///Display hands of cards on the console.
///</summary>
///<param name="hand"> Collection of Card objects representing a single hand. </param>
///<param name="leftIndex"> The starting index for the 'hand' collection, representing where the left collection begins. </param>
///<param name="midIndex"> Index denoting the middle point of the collection - to separate the 'left' and 'right' collections to be sorted/merged. </param>
///<param name="rightIndex"> The ending index to denote where the 'right' collection ends in the 'hand' collection. </param>
///<param name="temp"> Temporary collection of Card objects representing a single hand. </param>
///<returns> Nothing. </returns>
void Deck::mergeCollection(std::vector<Card> &hand, int leftIndex, int midIndex, int rightIndex, std::vector<Card> &temp)
{
	int i, j, k;

	i = leftIndex;
	j = midIndex;
	k = leftIndex;

	while (i < midIndex || j < rightIndex)
	{
		// If there are elements still left to compare between the two split arrays then do so
		if (i < midIndex && j < rightIndex)
		{
			if (hand.at(i) < hand.at(j))
			{
				temp.at(k++) = hand.at(i++);
			}
			else
			{
				temp.at(k++) = hand.at(j++);
			}
		}
		// If all elements in the "left" collection have been moved because they were less, add back the elements in the "right" collection
		else if (i == midIndex)
		{
			temp.at(k++) = hand.at(j++);
		}
		// Vice versa of the else if above
		else if (j == rightIndex)
		{
			temp.at(k++) = hand.at(i++);
		}
	}
}

#endif // !DECK_H