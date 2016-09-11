#pragma once
#include "BaseClasses.h"

class Pyromaniac :
	public Soul
{
public:
	Pyromaniac();
	~Pyromaniac();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};
