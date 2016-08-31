#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Soul.h"
#include "Player.h"

Soul::Soul(vector<int> Cost, string Name, string EffectText, string Description, _Color Color, _CardType CardType, vector<_EffectType> Effects, int OriginalAttack, int OriginalDefense) :
	Card(Cost, Name, EffectText, Description, Color, CardType, Effects), 
	OriginalAttack(OriginalAttack), OriginalDefense(OriginalDefense), 
	BaseAttack(OriginalAttack), BaseDefense(OriginalDefense), 
	CurrentAttack(OriginalAttack), CurrentDefense(OriginalDefense)
{
}

void Soul::Attacking(Soul* DefendingSoul)
{
	DefendingSoul->CurrentDefense = DefendingSoul->CurrentDefense - CurrentAttack;
	if (DefendingSoul->CurrentDefense < 0)
	{
		DefendingSoul->IsDead = true;
	}
}

void Soul::Attacking(Player* DefendingPlayer)
{
	DefendingPlayer->Health = DefendingPlayer->Health - CurrentAttack;
	if (DefendingPlayer->Health < 0)
	{
		DefendingPlayer->IsDead = true;
	}
}
