#pragma once
#include "BaseClasses.h"

class Hellspark_Mutt :
	public Creature
{
public:
	Hellspark_Mutt();
	~Hellspark_Mutt();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

