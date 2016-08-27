#pragma once
#include "Soul.h"
#include "Card.h"
class Fire_Spirit :
	public Soul
{
public:
	Fire_Spirit();
	~Fire_Spirit();
	virtual void Effect(GameState* CurrentGame);
};

