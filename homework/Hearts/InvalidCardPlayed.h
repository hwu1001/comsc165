#ifndef INVALIDCARDPLAYED_H
#define INVALIDCARDPLAYED_H
#include <string>

///<summary>
///InvalidCardPlayed object to handle when players try to select invalid choices for cards.
///</summary>
class InvalidCardPlayed
{
public:
	enum class ExceptionType
	{
		CAN_LEAD_QUEEN_OF_SPADES,
		CAN_HEARTS_BE_PLAYED,
		NOT_SAME_SUIT,
		CARD_IN_HAND,
		NONEXISTENT_CARD,
		BAD_LEADING_CARD,
		DUPLICATE_CARD
	};
	InvalidCardPlayed();
	InvalidCardPlayed(InvalidCardPlayed::ExceptionType exception);
	~InvalidCardPlayed();
	std::string getErrorDescription();

private:
	std::string m_errorDescription;
};

///<summary>
///Constructor for InvalidCardPlayed object.
///</summary>
///<returns> Nothing. </returns>
InvalidCardPlayed::InvalidCardPlayed()
{
}

///<summary>
///Constructor for InvalidCardPlayed object.
///</summary>
///<param name="exception"> The enum of the type of exception the player has encountered. </param>
///<returns> Nothing. </returns>
InvalidCardPlayed::InvalidCardPlayed(InvalidCardPlayed::ExceptionType exception)
{
	switch (exception)
	{
	case InvalidCardPlayed::ExceptionType::BAD_LEADING_CARD:
		m_errorDescription = "Must play the designated starting card in the first trick of a round.";
		break;
	case InvalidCardPlayed::ExceptionType::CAN_LEAD_QUEEN_OF_SPADES:
		m_errorDescription = "Cannot lead with Queen of Spades, when hand does not contain any Clubs.";
		break;
	case InvalidCardPlayed::ExceptionType::CAN_HEARTS_BE_PLAYED:
		m_errorDescription = "Hearts cannot be played yet.";
		break;
	case InvalidCardPlayed::ExceptionType::NOT_SAME_SUIT:
		m_errorDescription = "Player must play card of same suit as leading card if available.";
		break;
	case InvalidCardPlayed::ExceptionType::CARD_IN_HAND:
		m_errorDescription = "Card selected is not in player's hand.";
		break;
	case InvalidCardPlayed::ExceptionType::NONEXISTENT_CARD:
		m_errorDescription = "Card given does not exist.";
		break;
	case InvalidCardPlayed::ExceptionType::DUPLICATE_CARD:
		m_errorDescription = "Cards selected for passing cannot be duplicates.";
		break;
	default:
		break;
	}
}

///<summary>
///Destructor for InvalidCardPlayed object.
///</summary>
///<returns> Nothing. </returns>
InvalidCardPlayed::~InvalidCardPlayed()
{
}

///<summary>
///Getter for error description.
///</summary>
///<returns> String containing the error description. </returns>
inline std::string InvalidCardPlayed::getErrorDescription()
{
	return m_errorDescription;
}

#endif // !INVALIDCARDPLAYED_H