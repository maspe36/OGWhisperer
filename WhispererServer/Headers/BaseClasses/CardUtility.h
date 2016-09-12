#pragma once
#include "Card.h"

class GameState;

class CardUtility
{
public:
	static bool IsColorSoulPresent(GameState* CurrentGame, Card::_Color Color);
	static vector<string> GetUserSoulTarget();
	static vector<string> GetUserSoulOrPlayerTarget();
	~CardUtility();
private:
	CardUtility();
};

