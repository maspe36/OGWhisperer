#pragma once
#include "Player.h"
class GameState
{
public:
	GameState(Player* newPlayer1, Player* newPlayer2);
	Player* player1;
	Player* player2;
	~GameState();
};

