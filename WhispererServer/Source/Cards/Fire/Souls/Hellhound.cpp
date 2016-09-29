#include "Hellhound.h"

REGISTER_CLASS("Hellhound", Hellhound);

Hellhound::Hellhound() 
	: Soul({ 0,0,3,0,0,0 }, "Hellhound", "", "Rush", _Color::Fire, _CardType::_Soul, { _EffectType::Rush }, 3, 1)
{
	_Statis = 0;
	CanAttack = true;
}

Hellhound::~Hellhound()
{
}
