#pragma once

#include "Card.h"
#include "GameState.h"

class Soul :
	public Card
{
public:
	int Attack;
	int Defense;

	// ==================
	// Constructor Format
	// ==================

	// Card Cost
	// Card Name
	// Card EffectText
	// Card Description (Flavour text)
	// Card Color
	// Soul Attack
	// Soul Defense

	Soul(vector<int> Cost, string Name, string EffectText, string Description, string Color, int Attack, int Defense) :Card(Cost, Name, EffectText, Description, Color), Attack(Attack), Defense(Defense) {}
	void Attacking(Soul* DefendingSoul);
	void Attacking(Player* DefendingPlayer);

	virtual bool IsEffectTriggered(GameState* CurrentGame);
	virtual void Effect(GameState* CurrentGame);
};

