#pragma once
#include "Card.h"

class GameState;

class CardUtility
{
public:
	static bool IsColorCreaturePresent(GameState* CurrentGame, Card::_Color Color);
	static vector<string> GetUserCreatureTarget();
	static vector<string> GetUserCreatureOrPlayerTarget();
	~CardUtility();
private:
	CardUtility();
};

