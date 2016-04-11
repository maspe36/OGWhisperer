#pragma once
#include "Card.h"

class Soul :
	public Card
{
public:
	int Attack;
	int Defense;

	Soul(int Cost, string Name, string Description, int Attack, int Defense) :Card(Cost, Name, Description), Attack(Attack), Defense(Defense) {}
	void Attacking(Soul& DefendingSoul);
};
