#pragma once
#include "BaseClasses.h"

class Kindling :
	public Spell
{
public:
	Kindling();
	~Kindling();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

