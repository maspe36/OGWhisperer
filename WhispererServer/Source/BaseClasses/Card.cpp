#include "stdafx.h"
#include <string>
#include "Card.h"
#include "Soul.h"
#include "Player.h"

string Card::ToString()
{
	return Name;
}

Card::Card(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects) :
	Cost(Cost), Name(Name), FlavourText(FlavourText), EffectText(EffectText), Color(Color), CardType(CardType), Effects(Effects)
{
}

Card::~Card()
{
}

void Card::Effect(GameState* CurrentGame)
{
}

bool Card::IsEffectTriggered(Action* CurrentAction)
{
	return false;
}

void Card::Damage(vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense - this->_Damage;
	}
}

void Card::Damage(vector<Player*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health - this->_Damage;
	}
}

void Card::Heal(vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + this->_Heal;
	}
}

void Card::Heal(vector<Player*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health + this->_Heal;
	}
}

void Card::AttackChange(vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = this->_AttackChange;
	}
}

void Card::DefenseChange(vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseDefense = this->_DefenseChange;
	}
}