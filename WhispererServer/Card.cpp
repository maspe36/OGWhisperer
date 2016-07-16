#include "stdafx.h"
#include "Card.h"
#include <string>

Card::~Card()
{
}

string Card::ToString()
{
	// CardName
	return Name;
}
