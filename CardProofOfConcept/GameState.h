#pragma once
#include "Player.h"
#include "stdafx.h"

using namespace std;

class GameState
{
public:
	GameState(Player* newPlayer1, Player* newPlayer2);
	Player* player1;
	Player* player2;
	~GameState();

	void Start();
	string ToString(Player* ActivePlayer);
};

