#include "Fire_Spirit.h"

REGISTER_CLASS("Fire Spirit", Fire_Spirit);

Fire_Spirit::Fire_Spirit() 
	: Creature({ 0,0,1,0,0,0 }, "Fire Spirit", "", "A lonely spirit born from the inferno.", _Color::Fire, _CardType::_Creature, { _EffectType::Introduce }, 2, 1)
{
}

Fire_Spirit::~Fire_Spirit()
{
}
