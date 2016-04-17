#pragma once

#include "Deck.h"
#include "Soul.h"

class Player
{
public:
	Player();
	int Health = 30;
	Deck Deck;
	string UserName;
	vector<Soul*> SoulsInPlay;
	//vector<Swift*> SwiftsInPlay;
	//vector<Constant*> ConstantsInPlay;
};

