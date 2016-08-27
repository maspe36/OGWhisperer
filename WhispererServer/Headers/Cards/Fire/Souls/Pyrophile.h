#pragma once
#include "Soul.h"
class Pyrophile :
	public Soul
{
public:
	Pyrophile();
	~Pyrophile();
	virtual void Effect(GameState* CurrentGame);
};

