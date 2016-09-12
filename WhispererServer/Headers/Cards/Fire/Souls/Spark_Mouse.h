#pragma once
#include "BaseClasses.h"

class Spark_Mouse :
	public Soul
{
public:
	Spark_Mouse();
	~Spark_Mouse();
	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);
};

