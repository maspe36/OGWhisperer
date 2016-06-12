#include "stdafx.h"
#include "Soul.h"

void Soul::Attacking(Soul* DefendingSoul)
{
	DefendingSoul->Defense = DefendingSoul->Defense - Attack;
}

void Soul::Attacking(Player* DefendingPlayer)
{
	DefendingPlayer->Health = DefendingPlayer->Health - Attack;
}

bool Soul::IsEffectTriggered(GameState* CurrentGame)
{
	return false;
}

void Soul::Effect(GameState* CurrentGame)
{
}
