#pragma once

#include "Card.h"
#include "Player.h"

class Soul :
	public Card
{
public:
	int Attack;
	int Defense;

	Soul(int Cost, string Name, string EffectText, string Description, int Attack, int Defense) :Card(Cost, Name, EffectText, Description), Attack(Attack), Defense(Defense) {}
	void Attacking(Soul* DefendingSoul);
	void Attacking(Player* DefendingPlayer);
};

