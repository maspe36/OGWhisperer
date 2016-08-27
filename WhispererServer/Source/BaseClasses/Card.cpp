#include "stdafx.h"
#include <string>

#include "Card.h"

string Card::ToString()
{
	return Name;
}

Card::Card(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects) :
	Cost(Cost), Name(Name), FlavourText(FlavourText), EffectText(EffectText), Color(Color), CardType(CardType), Effects(Effects)
{
}

Card::~Card()
{
}

void Card::Effect(GameState* CurrentGame) 
{
}

bool Card::IsEffectTriggered(Action* CurrentAction) 
{
	return false;
}