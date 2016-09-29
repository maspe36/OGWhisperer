#include "stdafx.h"
#include <string>
#include "Card.h"
#include "Soul.h"
#include "Player.h"
#include "Action.h"
#include "Affect.h"
#include "GameState.h"

string Card::ToString()
{
	return Name;
}

Card::Card(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects) :
	Cost(Cost), Name(Name), FlavourText(FlavourText), EffectText(EffectText), Color(Color), CardType(CardType), Effects(Effects)
{
	IsDead = false;
	AppliedAffects = { new Affect(Card::_EffectType::None, this, "") };
}

Card::~Card()
{
}

void Card::Effect()
{
}

/* Function to check if the Action passed will trigger a cards effect. */
bool Card::IsEffectTriggered(Action* CurrentAction)
{
	return false;
}

/* Wrapper function to damage all souls in target vector for _Damage amount and then
create Action object and check the next layer of effects.  */
void Card::Damage(vector<Soul*> Targets, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Damage);

	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense - this->_Damage;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " took " << _Damage << " damage!" << endl;
		cout << Targets[i]->Name << " has " << Targets[i]->CurrentDefense << " health!" << endl;
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
		// Set the dead flag if the card is dead
		if (Targets[i]->CurrentDefense <= 0)
		{
			Targets[i]->IsDead = true;
		}
	}
	delete CurrentAction;
}

/* Wrapper function to damage all players in target vector for _Damage amount and then
create Action object and check the next layer of effects.  */
void Card::Damage(vector<Player*> Targets, Player* Owner)
{
	Action* CurrentAction = new Action(Targets, Owner, Action::_ActionType::Damage);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health - this->_Damage;
		cout << Targets[i]->UserName << " lost " << _Damage << " health!" << endl;
		cout << Targets[i]->UserName << " has " << Targets[i]->Health << " health!" << endl;
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
		// Set the dead flag if they are dead
		if (Targets[i]->Health <= 0)
		{
			Targets[i]->IsDead = true;
		}
	}
	delete CurrentAction;
}

/* Wrapper function to heal all souls in target vector for _Heal amount and then
create Action object and check the next layer of effects.  */
void Card::Heal(vector<Soul*> Targets, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Heal);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + this->_Heal;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " healed for " << _Heal << endl;
		cout << Targets[i]->Name << " has " << Targets[i]->CurrentDefense << " health!" << endl;
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

/* Wrapper function to heal all players in target vector for _Heal amount and then
create Action object and check the next layer of effects.  */
void Card::Heal(vector<Player*> Targets, Player* Owner)
{
	Action* CurrentAction = new Action(Targets, Owner, Action::_ActionType::Heal);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health + this->_Heal;
		cout << Targets[i]->UserName << " healed for " << _Heal << endl;
		cout << Targets[i]->UserName << " has " << Targets[i]->Health << " health!" << endl;
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

/* Wrapper function to buff all souls in target vector for _AttackBuff and _DefenseBuff amounts and then
create Action object and check the next layer of effects.  */
void Card::SoulBuff(vector<Soul*> Targets, Player * Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Buff);
	for (auto i : Targets) {
		i->BaseAttack = i->BaseAttack + _AttackBuff;
		i->CurrentAttack = i->CurrentAttack + _AttackBuff;
		i->BaseDefense = i->BaseDefense + _DefenseBuff;
		i->CurrentDefense = i->CurrentDefense + _DefenseBuff;
		i->AppliedAffects.push_back(CardAffect);
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
		cout << i->Name << " gained +" << _AttackBuff << "/+" << _DefenseBuff << endl;
	}
	delete CurrentAction;
}

void Card::SoulBuffNoTrigger(vector<Soul*> Targets, Player * Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Targets[i]->BaseAttack + _AttackBuff;
		Targets[i]->CurrentAttack = Targets[i]->CurrentAttack + _AttackBuff;
		Targets[i]->BaseDefense = Targets[i]->BaseDefense + _DefenseBuff;
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + _DefenseBuff;
		Targets[i]->AppliedAffects.push_back(CardAffect);
		cout << Targets[i]->Name << " gained " << CardAffect->Description << endl;
	}
}

/* Wrapper function to debuff all souls in target vector for _AttackDebuff and _DefenseDebuff amounts and then
create Action object and check the next layer of effects.  */
void Card::SoulDebuff(vector<Soul*> Targets, Player * Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Debuff);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Targets[i]->BaseAttack + _AttackDebuff;
		Targets[i]->CurrentAttack = Targets[i]->CurrentAttack + _AttackDebuff;
		Targets[i]->BaseDefense = Targets[i]->BaseDefense + _DefenseDebuff;
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + _DefenseDebuff;
		Targets[i]->AppliedAffects.push_back(CardAffect);
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
		cout << Targets[i]->Name << " lost " << CardAffect->Description << endl;
	}
	delete CurrentAction;
}

void Card::SoulDebuffNoTrigger(vector<Soul*> Targets, Player * Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Targets[i]->BaseAttack + _AttackDebuff;
		Targets[i]->CurrentAttack = Targets[i]->CurrentAttack + _AttackDebuff;
		Targets[i]->BaseDefense = Targets[i]->BaseDefense + _DefenseDebuff;
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + _DefenseDebuff;
		Targets[i]->AppliedAffects.push_back(CardAffect);
		cout << Targets[i]->Name << " lost " << CardAffect->Description << endl;
	}
}
