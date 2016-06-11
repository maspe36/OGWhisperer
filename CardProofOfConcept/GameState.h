#pragma once
#include "Player.h"
#include "stdafx.h"

using namespace std;

class GameState
{
public:
	GameState(vector<Player*> Players);
	vector<Player*> PlayersInGame;
	Player* ActivePlayer;
	~GameState();

	void Start();
	void ChangeActivePlayer();
	void StartOfTurnEffects();
};

