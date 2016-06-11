#include "stdafx.h"
#include <string>
#include "BaseClasses.h"
using namespace std;

Player::Player()
{
}

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

Player::Player(Deck NewDeck, string NewUserName)
{
	MainDeck = NewDeck;
	UserName = NewUserName;
}

void Player::PlayCard(int index)
{
	Card* FromHand = Hand.at(index);

	Soul *SoulCard = nullptr;
	//Type2 *t2 = nullptr;
	//Type3 *t3 = nullptr;

	if (SoulCard = dynamic_cast<Soul*>(FromHand))
	{
		//Logically put the card in play
		SoulsInPlay.push_back(SoulCard);
		//Declare it has entered play
		cout << SoulCard->Name << " has entered the field for " << UserName << endl;
		//Remove the card from the hand if it succesfully enters the field
		Hand.erase(Hand.begin() + index);
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

void Player::DrawCard()
{
	Hand.push_back(MainDeck.Draw());
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

