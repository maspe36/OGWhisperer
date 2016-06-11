#pragma once

#include "Deck.h"

class Soul;

class Player
{
public:
	Player();
	~Player();
	Player(Deck NewDeck, string NewUserName);
	int Health = 30;
	Deck MainDeck;
	string UserName;
	vector<Card*> Hand;
	vector<Soul*> SoulsInPlay;
	//vector<Swift*> SwiftsInPlay;
	//vector<Constant*> ConstantsInPlay;
	vector<Card*> Graveyard;

	void PlayCard(int index);
	void DrawCard();
	string HandToString();
	string ToString();
	string SoulsInPlayToString();
	bool Compare(Player* OtherPlayer);
};

