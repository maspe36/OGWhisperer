#pragma once
#include "Soul.h"
class Hellhound :
	public Soul
{
public:
	Hellhound() : Soul(3, "Hellhound", "Rush", 3, 1) {}
	~Hellhound();
};

