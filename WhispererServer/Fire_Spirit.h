#pragma once
#include "Soul.h"
#include "Card.h"
class Fire_Spirit :
	public Soul
{
public:
	Fire_Spirit() : Soul({ 0,0,1,0,0,0 }, "Fire Spirit", "", "A lonely spirit born from the inferno.", "Red", 2, 1) {}
	~Fire_Spirit();
};

