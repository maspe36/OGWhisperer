#include "stdafx.h"
#include "Soul.h"
#include "Fire_Spirit.h"
#include "Action.h"
#include "Player.h"
#include "Constant.h"
#include "CardUtility.h"

Fire_Spirit::Fire_Spirit() 
	: Soul({ 0,0,1,0,0,0 }, "Fire Spirit", "", "A lonely spirit born from the inferno.", _Color::Fire, _CardType::_Soul, { _EffectType::Introduce }, 2, 1)
{
}

Fire_Spirit::~Fire_Spirit()
{
}
