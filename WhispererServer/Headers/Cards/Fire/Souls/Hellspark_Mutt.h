#pragma once
#include "BaseClasses.h"

class Hellspark_Mutt :
	public Soul
{
public:
	Hellspark_Mutt();
	~Hellspark_Mutt();
	virtual void Effect(GameState* CurrentGame);
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

