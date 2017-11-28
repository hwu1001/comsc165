// Henry Wu
// COMSC 165
// Section 3015
// Homework 6

#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "InvalidCardPlayed.h"
#include "HeartsGame.h"

using namespace std;

int main()
{
	int numPlayers;
	bool valid;
	cout << "Hearts" << '\n';
	do
	{
		cout << "How many players in the game? (3-5) ";
		cin >> numPlayers;
		valid = HeartsGame::isValidNumberOfPlayers(numPlayers);
		if (!valid)
		{
			cout << "Invalid number of players. Please re-enter." << '\n';
		}
	} while (!valid);

	HeartsGame game(numPlayers);
	game.start();

	return 0;
}
