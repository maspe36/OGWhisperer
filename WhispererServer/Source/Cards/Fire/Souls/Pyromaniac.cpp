#include "stdafx.h"
#include "Pyromaniac.h"
#include "Card.h"

Pyromaniac::Pyromaniac() 
	: Soul({ 0,0,4,0,0,0 }, "Pyromaniac", "", "Downfall - Deal 2 damage to target player or soul", _Color::Fire, _CardType::_Soul, { _EffectType::Downfall }, 3, 4)
{
}

Pyromaniac::~Pyromaniac()
{
}

