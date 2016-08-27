#pragma once
#include "Soul.h"
class Pyromaniac :
	public Soul
{
public:
	Pyromaniac();
	~Pyromaniac();
	virtual void Effect(GameState* CurrentGame);
};
