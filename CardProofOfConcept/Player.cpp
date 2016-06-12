#include "stdafx.h"
#include <string>
#include "BaseClasses.h"
using namespace std;

Player::~Player()
{
	//Delete the hand
	for (auto i : Hand) {
		delete i;
	}
	//Delete the souls in play
	for (auto i : SoulsInPlay) {
		delete i;
	}
	////Delete the constants in play
	//for (auto i : ConstatnsInPlay) {
	//	delete i;
	//}
	////Delete the swifts in play
	//for (auto i : SwiftsInPlay) {
	//	delete i;
	//}
}

Player::Player(vector<Card*> NewDeck, string NewUserName) : MainDeck(NewDeck), UserName(NewUserName)
{
	ShuffleDeck();
}

void Player::DrawCard()
{
	Card* temp = MainDeck.front();

	MainDeck.erase(MainDeck.begin());

	Hand.push_back(temp);
}

string Player::HandToString()
{
	string CardsInHand;

	for (auto i : Hand) {
		CardsInHand += (i->ToString() + "#");
	}

	return CardsInHand;
}

string Player::ToString()
{
	//PlayerName+PlayerHealth
	return UserName + "+" + to_string(Health);
}

//Do I have a memory leak here? How can I free this memory?
string Player::SoulsInPlayToString()
{
	string SoulsInPlayString;

	for (auto i : SoulsInPlay) {
		SoulsInPlayString += (i->ToString() + "#");
	}

	return SoulsInPlayString;
}

bool Player::Compare(Player * OtherPlayer)
{
	// If username is not sufficent...
	// Must compare the following...
	// Health
	// Deck Contents
	// Username
	// Hand Contents
	// Souls on Field
	// Swifts on Field
	// Constants on Field
	// Graveyard

	// But for now we will assume that the username is sufficent enough
	if (UserName.compare(OtherPlayer->UserName) != 0){
		return false;
	}
	else {
		return true;
	}
}

void Player::ShuffleDeck()
{
	vector<Card*> Copy(MainDeck);
	int Max, Current;

	Max = MainDeck.size();

	MainDeck.clear();
	//Seed rand()
	srand(time(NULL));

	for (int Counter = 0; Counter < Max; Counter++)
	{
		Current = rand() % Copy.size();
		MainDeck.push_back(Copy[Current]);
		Copy.erase(Copy.begin() + Current);
	}
}

