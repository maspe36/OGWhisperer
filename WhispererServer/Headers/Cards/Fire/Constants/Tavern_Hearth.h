#pragma once
#include "BaseClasses.h"

class Tavern_Hearth :
	public Constant
{
public:
	Tavern_Hearth();
	~Tavern_Hearth();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

