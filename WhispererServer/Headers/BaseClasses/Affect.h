#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
// We need to break our standard here because otherwise we create redundant enums
#include "Card.h"

class Affect
{
public:
	Card::_EffectType EffectType;
	Card* Owner;
	string Description;

	Affect(Card::_EffectType EffectType, Card* Owner, string Description);
	~Affect();

	string ToString();
};

