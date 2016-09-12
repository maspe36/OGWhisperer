#include "Swift.h"

Swift::Swift(vector<int> Cost, string Name, string EffectText, string Description, _Color Color, _CardType CardType, vector<_EffectType> Effects) 
	: Card(Cost, Name, FlavourText, EffectText, Color, CardType, Effects)
{
}

Swift::~Swift()
{
}
