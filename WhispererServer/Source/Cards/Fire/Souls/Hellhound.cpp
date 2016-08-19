#include "stdafx.h"
#include "Hellhound.h"

Hellhound::Hellhound() 
	: Soul({ 0,0,3,0,0,0 }, "Hellhound", "Rush", "", _Color::Fire, _CardType::Soul, { _EffectType::Rush }, 3, 1)
{
}

Hellhound::~Hellhound()
{
}
