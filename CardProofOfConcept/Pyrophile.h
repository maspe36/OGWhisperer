#pragma once
#include "Soul.h"
class Pyrophile :
	public Soul
{
public:
	Pyrophile() : Soul(4, "Pyrophile", "Introduce - Add a swift that deals 3 or less damage from your deck to your hand.", "", 2, 3) {}
	~Pyrophile();
};

