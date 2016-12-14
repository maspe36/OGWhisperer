#pragma once
#include "BaseClasses.h"

class Pyromaniac :
	public Creature
{
public:
	Pyromaniac();
	~Pyromaniac();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};
