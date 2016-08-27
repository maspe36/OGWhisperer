#pragma once
#include "Soul.h"
class Hellhound :
	public Soul
{
public:
	Hellhound();
	~Hellhound();
	virtual void Effect(GameState* CurrentGame);
};

