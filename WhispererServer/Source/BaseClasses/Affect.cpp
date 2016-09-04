#include "Affect.h"

Affect::Affect(Card::_EffectType EffectType, Card* Owner, string Description) 
	: EffectType(EffectType), Owner(Owner), Description(Description)
{
}


Affect::~Affect()
{
}

string Affect::ToString()
{
	return Description + " from " + Owner->Name;
}
