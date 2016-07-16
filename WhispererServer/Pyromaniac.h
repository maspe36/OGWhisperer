#pragma once
#include "Soul.h"
class Pyromaniac :
	public Soul
{
public:
	Pyromaniac() : Soul({ 0,0,4,0,0,0 }, "Pyromaniac", "Downfall - Deal 2 damage to target player or soul", "", "Red", 3, 4) {}
	~Pyromaniac();
};
