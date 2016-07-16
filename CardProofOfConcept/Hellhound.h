#pragma once
#include "Soul.h"
class Hellhound :
	public Soul
{
public:
	Hellhound() : Soul({ 0,0,3,0,0,0 }, "Hellhound", "Rush", "", "Red", 3, 1) {}
	~Hellhound();
};

