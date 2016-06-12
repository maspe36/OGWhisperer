#pragma once

#include "stdafx.h"
#include <vector>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <memory>
#include "Card.h"

class Soul;

class Player
{
public:
	~Player();
	Player(vector<Card*> NewDeck, string NewUserName);
	int Health = 30;
	string UserName;

	vector<Card*> MainDeck;
	vector<Card*> Hand;
	vector<Soul*> SoulsInPlay;
	//vector<Swift*> SwiftsInPlay;
	//vector<Constant*> ConstantsInPlay;
	vector<Card*> Graveyard;

	void DrawCard();
	string HandToString();
	string ToString();
	string SoulsInPlayToString();
	bool Compare(Player* OtherPlayer);
	void ShuffleDeck();
};

