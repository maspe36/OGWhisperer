#pragma once
#include <iostream>
#include <vector>

#include "Card.h"

class Player;

class Soul :
	public Card
{
public:
	// Original Card stats
	int const OriginalAttack;
	int const OriginalDefense;
	// Current Base Card stats (From buffs, debuffs, etc)
	int BaseAttack;
	int BaseDefense;
	// Current stats as is
	int CurrentAttack;
	int CurrentDefense;

	// This is essentially how we deal with 
	// summoning sickness, this number should be reduced each turn
	// until it is zero. If statis is zero it can attack?
	int _Statis = 1;
	// Number of attacks a soul has left
	int _Flurry = 1;
	int _OriginalFlurry = 1;
	bool CanAttack;

	Soul(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects, int OriginalAttack, int OriginalDefense);

	void PreAttackMaintenance();
	void Attacking(Soul* DefendingSoul);
	void Attacking(Player* DefendingPlayer);
};
