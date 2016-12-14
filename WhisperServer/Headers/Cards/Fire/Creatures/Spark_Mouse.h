#pragma once
#include "BaseClasses.h"

class Spark_Mouse :
	public Creature
{
public:
	Spark_Mouse();
	~Spark_Mouse();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

