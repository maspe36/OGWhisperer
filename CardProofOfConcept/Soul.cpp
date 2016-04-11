#include "stdafx.h"
#include "Soul.h"

void Soul::Attacking(Soul& DefendingSoul)
{
	DefendingSoul.Defense = DefendingSoul.Defense - Attack;
}
