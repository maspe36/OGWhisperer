#pragma once
#include "BaseClasses.h"

class Action;

class Constant :
	public Card
{
public:
	Constant(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects);
	~Constant();
	void IsDeadMaintenance();
	void RemoveEffect(Card* Target);
};

