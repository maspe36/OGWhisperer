#pragma once

#include "Deck.h"

class Soul;

class Player
{
public:
	Player();
	int Health = 30;
	Deck Deck;
	string UserName;
	vector<Card*> Hand;
	vector<Soul*> SoulsInPlay;
	//vector<Swift*> SwiftsInPlay;
	//vector<Constant*> ConstantsInPlay;
	void PlayCard(vector<Card*>& Hand, int index);
	void PrintHand();
};

