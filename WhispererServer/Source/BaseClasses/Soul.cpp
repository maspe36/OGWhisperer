#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Soul.h"
#include "Player.h"

Soul::Soul(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects, int OriginalAttack, int OriginalDefense) :
	Card(Cost, Name, FlavourText, EffectText, Color, CardType, Effects),
	OriginalAttack(OriginalAttack), OriginalDefense(OriginalDefense), 
	BaseAttack(OriginalAttack), BaseDefense(OriginalDefense), 
	CurrentAttack(OriginalAttack), CurrentDefense(OriginalDefense)
{
	CanAttack = false;
}

/* Applies damage to the target soul from the soul calling the function.
 Then the soul that called the function has damage applied to it equal to the
 target soul's current attack. If either soul's current defense is below zero
 the IsDead flag is set. */
void Soul::Attacking(Soul* DefendingSoul)
{
	DefendingSoul->CurrentDefense = DefendingSoul->CurrentDefense - CurrentAttack;
	CurrentDefense = CurrentDefense - DefendingSoul->CurrentAttack;
	if (DefendingSoul->CurrentDefense <= 0)
	{
		DefendingSoul->IsDead = true;
	}
	if (CurrentDefense <= 0) 
	{
		IsDead = true;
	}
}

/* Applies damage to the target player equal to soul that called this function's attack.
If the target players health is below 0 the IsDead flag is set. */
void Soul::Attacking(Player* DefendingPlayer)
{
	DefendingPlayer->Health = DefendingPlayer->Health - CurrentAttack;
	if (DefendingPlayer->Health <= 0)
	{
		DefendingPlayer->IsDead = true;
	}
}
