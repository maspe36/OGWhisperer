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

	Soul(vector<int> Cost, string Name, string EffectText, string Description, _Color Color, _CardType CardType, vector<_EffectType> Effects, int OriginalAttack, int OriginalDefense);
	
	void Attacking(Soul* DefendingSoul);
	void Attacking(Player* DefendingPlayer);
};

