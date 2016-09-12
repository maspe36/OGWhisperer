#pragma once
#include <iostream>
#include <vector>

/* At some point there will
   probably need to be a unique
   hash in all objects for each game */

using namespace std;

class GameState;
class Affect;
class Action;
class Player;
class Soul;

class Card
{
public:
	/* Order of colors in cost vector (Alphabetical)
	   0: Dark
	   1: Earth
	   2: Fire
	   3: Light
	   4: Water
	   5: Wind */
	vector<int> Cost;
	// Name of the card
	string Name;
	// The flavour text of a card
	string FlavourText;
	// The effect of a card in text
	string EffectText;
	// The color of a card
	enum _Color
	{
		Dark,
		Earth,
		Fire,
		Light,
		Water,
		Wind
	} Color;
	// Base Card Types
	enum _CardType
	{
		_Constant,
		_Soul,
		_Swift
	} CardType;
	// Different possible effect types
	enum _EffectType
	{
		None,
		Buff,
		Debuff,
		Continuous,
		Downfall,
		HighTide,
		InHand,
		Introduce,
		OnDiscard,
		OnDraw,
		Rush,
		Statis,
		Trigger,
		TurnStart,
		TurnEnd
	} EffectType;

	vector<_EffectType> Effects;
	Player* Owner;

	bool IsDead;
	vector<Affect*> AppliedAffects;

	int _Damage = 0;
	int _Heal = 0;
	int _AttackBuff = 0;
	int _AttackDebuff = 0;
	int _DefenseBuff = 0;
	int _DefenseDebuff = 0;
	vector<int> HighTideCost = { 99,99,99,99,99,99 };

	virtual string ToString();

	void Damage(vector<Soul*> Targets, Player* Owner);
	void Damage(vector<Player*> Targets, Player* Owner);

	void Heal(vector<Soul*> Targets, Player* Owner);
	void Heal(vector<Player*> Targets, Player* Owner);

	void SoulBuff(vector<Soul*> Targets, Player* Owner);
	void SoulDebuff(vector<Soul*> Targets, Player* Owner);

	virtual void Effect();
	virtual bool IsEffectTriggered(Action* CurrentAction);

	Card(vector<int> Cost, string Name, string EffectText, string FlavourText,
		_Color Color, _CardType CardType, vector<_EffectType> Effects);
	virtual ~Card();
};
