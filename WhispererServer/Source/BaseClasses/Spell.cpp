#include "Spell.h"
#include <string>

Spell::Spell(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects)
	: Card(Cost, Name, FlavourText, EffectText, Color, CardType, Effects)
{
}

Spell::~Spell()
{
}
