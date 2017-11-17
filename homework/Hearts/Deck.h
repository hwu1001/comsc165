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
	static void sort(std::vector<Card> &hand);
	std::vector<std::vector<Card>> deal(int numHands, int handSize);
	static void display(std::vector<std::vector<Card>> &handCollection);

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
	srand(time(0));
	int random;
	// Could use std::random_shuffle, but we can implement Fisher-Yates shuffle
	for (int i = m_cards.size() - 1; i > 0; i--)
	{
		random = rand() % 52;
		iter_swap(m_cards.begin() + i, m_cards.begin() + random);
	}
}

///<summary>
///Sorts a given hand of Card objects in order based on suit and card value.
///Suit priority from lowest to highest: Clubs, Diamonds, Hearts, Spades
///Card value priority from lowest to highest: 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace
///</summary>
///<param name="hand"> Collection of Card objects representing a single hand to be sorted. </param>
///<returns> Nothing. </returns>
void Deck::sort(std::vector<Card> &hand)
{
	//Merge sort
	mergeSort(hand);
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
///Display hands of cards on the console.
///</summary>
///<param name="handCollection"> A vector holding vectors of Card objects representing hands of cards. </param>
///<returns> Nothing. </returns>
void Deck::display(std::vector<std::vector<Card>> &handCollection)
{
	system("cls");
	int collectionSize = handCollection.size();
	int handSize = handCollection.at(0).size(); // all hand sizes are the same
	std::string tempStr;

	std::cout << std::left;
	for (int i = 0; i < collectionSize; i++)
	{
		tempStr = "Hand " + std::to_string(i + 1);
		std::cout << std::setw(19) << tempStr;
	}
	std::cout << '\n';
	for (int i = 0; i < collectionSize; i++)
	{
		std::cout << std::setw(19) << "======";
	}
	std::cout << '\n';
	for (int i = 0; i < handSize; i++)
	{
		for (int j = 0; j < collectionSize; j++)
		{
			std::cout << std::setw(19) << std::left << handCollection.at(j).at(i).getDescription();
		}
		std::cout << '\n';
	}

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
