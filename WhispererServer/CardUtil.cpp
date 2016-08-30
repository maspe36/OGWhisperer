#include "CardUtil.h"
#include "Card.h"
#include "Soul.h"
#include "Player.h"

CardUtil::CardUtil()
{
}

void CardUtil::Damage(Card * Source, vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense - Source->_Damage;
	}
}

void CardUtil::Damage(Card * Source, vector<Player*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health - Source->_Damage;
	}
}

void CardUtil::Heal(Card * Source, vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + Source->_Heal;
	}
}

void CardUtil::Heal(Card * Source, vector<Player*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health + Source->_Heal;
	}
}

void CardUtil::AttackChange(Card * Source, vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Source->_AttackChange;
	}
}

void CardUtil::DefenseChange(Card * Source, vector<Soul*> Targets)
{
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseDefense = Source->_DefenseChange;
	}
}

CardUtil::~CardUtil()
{
}
