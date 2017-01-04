#include "Pyrophile.h"

REGISTER_CLASS("Pyrophile", Pyrophile);

Pyrophile::Pyrophile() 
	: Creature({ 0,0,4,0,0,0 }, "Pyrophile", "", "Introduce - Add a spell that deals 3 or less damage from your deck to your hand.", _Color::Fire, _CardType::_Creature, { _EffectType::Introduce }, 2, 3)
{
}

Pyrophile::~Pyrophile()
{
}
