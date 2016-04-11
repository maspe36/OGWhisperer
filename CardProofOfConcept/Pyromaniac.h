#pragma once
#include "Soul.h"
class Pyromaniac :
	public Soul
{
public:
	Pyromaniac() : Soul(2, "Pyromaniac", "This man loves his fire.", 3, 4) {}
	~Pyromaniac();
};
