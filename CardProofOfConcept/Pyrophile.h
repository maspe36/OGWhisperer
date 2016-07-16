#pragma once
#include "Soul.h"
class Pyrophile :
	public Soul
{
public:
	Pyrophile() : Soul({ 0,0,4,0,0,0 }, "Pyrophile", "Introduce - Add a swift that deals 3 or less damage from your deck to your hand.", "", "Red", 2, 3) {}
	~Pyrophile();
};

