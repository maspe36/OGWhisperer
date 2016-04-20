#include "stdafx.h"
#include "Card.h"
#include <string>

string Card::ToString()
{
	//CardName+CardCost+CardDescription
	return Name + "+" + to_string(Cost) + "+" + Description;
}
