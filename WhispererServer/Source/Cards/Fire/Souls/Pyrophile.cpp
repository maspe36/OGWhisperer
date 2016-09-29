#include "Pyrophile.h"

REGISTER_CLASS("Pyrophile", Pyrophile);

Pyrophile::Pyrophile() 
	: Soul({ 0,0,4,0,0,0 }, "Pyrophile", "", "Introduce - Add a swift that deals 3 or less damage from your deck to your hand.", _Color::Fire, _CardType::_Soul, { _EffectType::Introduce }, 2, 3)
{
}

Pyrophile::~Pyrophile()
{
}
