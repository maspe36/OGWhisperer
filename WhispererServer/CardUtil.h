#pragma once

#include <vector>
#include <iostream>

class Soul;
class Player;
class Card;

using namespace std;

class CardUtil
{
public:
	CardUtil();

	void Damage(vector<Soul*> Targets);
	void Damage(vector<Player*> Targets);

	void Heal(vector<Soul*> Targets);
	void Heal(vector<Player*> Targets);

	void AttackChange(vector<Soul*> Targets);
	void DefenseChange(vector<Soul*> Targets);

	~CardUtil();
};

