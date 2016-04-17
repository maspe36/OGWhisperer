#pragma once

#include "Deck.h"

class Soul;

class Player
{
public:
	Player();
	Player(Deck NewDeck, string NewUserName);
	int Health = 30;
	Deck MainDeck;
	string UserName;
	vector<Card*> Hand;
	vector<Soul*> SoulsInPlay;
	//vector<Swift*> SwiftsInPlay;
	//vector<Constant*> ConstantsInPlay;
	void PlayCard(int index);
	void PrintHand();
	void DrawCard();
};

