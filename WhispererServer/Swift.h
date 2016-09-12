#pragma once
#include "Card.h"

class Swift :
	public Card
{
public:
	Swift(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects);
	~Swift();
};

