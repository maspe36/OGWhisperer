#pragma once
#include "Soul.h"
class Hellspark_Mutt :
	public Soul
{
public:
	Hellspark_Mutt() : Soul(3, "Hellspark Mutt", "Introduce - Deal 1 damage to target soul or player.", "", 3, 2) {}
	~Hellspark_Mutt();
	void Effect(GameState* CurrentGame);
};

