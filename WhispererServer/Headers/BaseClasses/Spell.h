#pragma once
#include "Card.h"
class Spell :
	public Card
{
public:
	Spell(vector<int> Cost, string Name, string EffectText, string Description, _Color Color, _CardType CardType, vector<_EffectType> Effects);
	~Spell();
};

