#pragma once
#include "Player.h"
#include "stdafx.h"

using namespace std;

class Soul;

class GameState
{
public:
	GameState(vector<Player*> Players);
	vector<Player*> PlayersInGame;
	Player* ActivePlayer;
	vector<Card*> Stack; // Stack is the order of cards that entered the field so we can resolve effects
	~GameState();

	void Start();
	void MulliganState();
	void PlayState();
	void ChangeActivePlayer();
	void PlayCard(Player * CardOwner, int HandIndex);
};

