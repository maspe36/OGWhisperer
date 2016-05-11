#pragma once
#include "Player.h"
#include "stdafx.h"

using namespace std;

class GameState
{
public:
	GameState(Player* newPlayer1, Player* newPlayer2);
	vector<Player*> PlayersInGame;
	Player* ActivePlayer;
	~GameState();

	void Start();
	void ChangeActivePlayer();
	void StartOfTurnEffects();
	string ToString(Player* RecivingGameStatePlayer);
};

