#pragma once
#include "Soul.h"
#include "Card.h"
class Fire_Spirit :
	public Soul
{
public:
	Fire_Spirit() : Soul(1, "Fire Spirit", "", "A lonely spirit born from the inferno.", 2, 1) {}
	~Fire_Spirit();
};

