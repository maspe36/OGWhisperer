#include "stdafx.h"
#include <string>
#include "BaseClasses.h"
using namespace std;

Player::Player()
{
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

void Player::PrintHand()
{
	for (auto i : Hand)
		cout << i->Name << endl;
}

void Player::DrawCard()
{
	Hand.push_back(MainDeck.Draw());
}

