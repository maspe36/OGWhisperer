#pragma once
#include "Card.h"
class Swift :
	public Card
{
public:
	Swift(vector<int> Cost, string Name, string EffectText, string Description, _Color Color, _CardType CardType, vector<_EffectType> Effects);
	~Swift();
};

