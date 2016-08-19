#include "stdafx.h"
#include <string>

#include "Card.h"

string Card::ToString()
{
	return Name;
}

Card::Card(vector<int> Cost, string Name, string EffectText, string FlavourText, _Color Color, _CardType CardType, vector<_EffectType> Effects) :
	Cost(Cost), Name(Name), EffectText(EffectText), FlavourText(FlavourText), Color(Color), CardType(CardType), Effects(Effects)
{
}

Card::~Card()
{
}


