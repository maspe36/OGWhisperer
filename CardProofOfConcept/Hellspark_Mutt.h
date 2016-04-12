#pragma once
#include "Soul.h"
class Hellspark_Mutt :
	public Soul
{
public:
	Hellspark_Mutt() : Soul(3, "Hellspark Mutt", "Downfall: Deal 1 damage to target soul or player.", 2, 2) {}
	~Hellspark_Mutt();
};

