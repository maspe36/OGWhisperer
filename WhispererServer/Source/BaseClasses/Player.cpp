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
	if (UserName.compare(OtherPlayer->UserName) != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Player::IsPlayable(Card * ToPlay)
{
	return false;
}

void Player::DrawCard()
{
	Card* temp = MainDeck.front();

	MainDeck.erase(MainDeck.begin());

	Hand.push_back(temp);
}

void Player::DrawCard(int Amount)
{
	for (int i = 0; i < Amount; i++) {
		Card* temp = MainDeck.front();

		MainDeck.erase(MainDeck.begin());

		Hand.push_back(temp);
	}
}

void Player::ShuffleDeck()
{
	vector<Card*> Copy(MainDeck);
	int Max, Current;

	Max = MainDeck.size();

	MainDeck.clear();
	//Seed rand()
	srand((unsigned int)time(NULL));

	for (int Counter = 0; Counter < Max; Counter++)
	{
		Current = rand() % Copy.size();
		MainDeck.push_back(Copy[Current]);
		Copy.erase(Copy.begin() + Current);
	}
}

void Player::HandToDeck()
{
	for (size_t i = 0; i < Hand.size(); i++) {
		Card* temp = Hand[i];

		MainDeck.push_back(temp);
	}
	Hand.clear();
}

void Player::PlayCard(Card* ToPlay, string Detail)
{
	Soul *SoulCard = nullptr;
	//Type2 *t2 = nullptr;
	//Type3 *t3 = nullptr;

	if (SoulCard = dynamic_cast<Soul*>(ToPlay))
	{
		// Logically put the card in play
		SoulsInPlay.push_back(SoulCard);
		// Declare it has entered play
		cout << SoulCard->Name << " has entered the field for " << UserName << endl;
		// Remove the card from the hand if it succesfully enters the field
		Hand.erase(Hand.begin() + stoi(Detail));
	}
	// if (t2 = dynamic_cast<Type2*>(p))
	//{
	//t2->type2Method();
	//}
	//else if (t3 = dynamic_cast<Type3*>(p))
	//{
	//t3->type3Method();
	//}
}

