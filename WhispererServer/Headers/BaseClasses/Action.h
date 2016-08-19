#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Player;
class Card;

class Action
{
public:
	vector<Card*> CardTargets;
	vector<Player*> PlayerTargets;
	Player* Owner;

	enum _ActionType
	{
		Damage,
		Heal,
		Buff,
		Debuff,
		Draw,
		Discard,
		Summon,
		Destroy
	} ActionType;

	Action();
	// Only card targets
	Action(vector<Card*> CardTargets, Player* Owner, _ActionType ActionType);
	// Only player targets
	Action(vector<Player*> PlayerTargets, Player* Owner, _ActionType ActionType);
	// Card AND player targets
	Action(vector<Card*> CardTargets, vector<Player*> PlayerTargets, Player* Owner, _ActionType ActionType);
	~Action();
};

