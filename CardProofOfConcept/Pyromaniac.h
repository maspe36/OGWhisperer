#pragma once
#include "Soul.h"
class Pyromaniac :
	public Soul
{
public:
	Pyromaniac() : Soul(4, "Pyromaniac", "Downfall - Deal 2 damage to target player or soul", "", 3, 4) {}
	~Pyromaniac();
};
