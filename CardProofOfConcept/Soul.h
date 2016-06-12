#pragma once

#include "Card.h"
#include "GameState.h"

class Soul :
	public Card
{
public:
	int Attack;
	int Defense;

	Soul(int Cost, string Name, string EffectText, string Description, int Attack, int Defense) :Card(Cost, Name, EffectText, Description), Attack(Attack), Defense(Defense) {}
	void Attacking(Soul* DefendingSoul);
	void Attacking(Player* DefendingPlayer);

	virtual bool IsEffectTriggered(GameState* CurrentGame);
	virtual void Effect(GameState* CurrentGame);
};

