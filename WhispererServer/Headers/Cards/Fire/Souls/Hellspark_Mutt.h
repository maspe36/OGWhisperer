#pragma once
#include "Soul.h"
class Hellspark_Mutt :
	public Soul
{
public:
	Hellspark_Mutt() : Soul({ 0,0,3,0,0,0 }, "Hellspark Mutt", "Introduce - Deal 1 damage to target soul or player.", "", "Red", 3, 2) {}
	~Hellspark_Mutt();
	void Effect(GameState* CurrentGame);
};

