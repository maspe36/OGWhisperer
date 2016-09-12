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
	return "\"card\":{" + JsonInfo() + "}";
}

string Card::JsonInfo()
{
	ostringstream os;
	os
		<< "\"name\":" << '"' << Name << '"' << ','
		<< "\"cost\":" << '{'
		<< "\"dark\":" << '"' << Cost[0] << '"' << ','
		<< "\"earth\":" << '"' << Cost[1] << '"' << ','
		<< "\"fire\":" << '"' << Cost[2] << '"' << ','
		<< "\"light\":" << '"' << Cost[3] << '"' << ','
		<< "\"water\":" << '"' << Cost[4] << '"' << ','
		<< "\"wind\":" << '"' << Cost[5] << '"'
		<< '}' << ','
		<< "\"effectText\":" << '"' << EffectText << '"' << ','
		<< "\"flavorText\":" << '"' << FlavourText << '"' << ','
		<< "\"color\":" << '"' << Color << '"' << ','
		<< "\"cardType\":" << '"' << CardType << '"' << ','
		<< "\"owner\":" << '"' << Owner->UserName << '"' << ','
		<< "\"effects\":" << '[';
	// Until the last one
	for (size_t i = 0; i < Effects.size() - 1; i++)
	{
		os << '"' << Effects[i] << '"' << ',';
	}
	if(Effects.back() != _EffectType::None)
	{
		os << '"' << Effects.back() << '"';
	}
	
	// Fill affects, don't put anything in if it has _EffectType::None.
	os
		<< ']' << ','
		<< "\"affects\":" << '[';
	for (size_t t = 0; t < AppliedAffects.size() - 1; t++)
	{
		os << '"' << AppliedAffects[t]->EffectType << '"' << ',';
	}
	if (AppliedAffects.back()->EffectType != _EffectType::None)
	{
		os << '"' << AppliedAffects.back()->EffectType << '"' << ',';
	}

	os 
		<< ']' << ','
		<< "\"highTideCost\":" << '{';
	if (HighTideCost[0] != 99)
	{
		os
			<< "\"dark\":" << '"' << HighTideCost[0] << '"' << ','
			<< "\"earth\":" << '"' << HighTideCost[1] << '"' << ','
			<< "\"fire\":" << '"' << HighTideCost[2] << '"' << ','
			<< "\"light\":" << '"' << HighTideCost[3] << '"' << ','
			<< "\"water\":" << '"' << HighTideCost[4] << '"' << ','
			<< "\"wind\":" << '"' << HighTideCost[5] << '"';
	}
	os << '}';

	return os.str();
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
	Affect* CurrentAffect = new Affect(Card::_EffectType::Buff, this, ("+" + to_string(_AttackBuff) + "/+" + to_string(_DefenseBuff)));
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Targets[i]->BaseAttack + _AttackBuff;
		Targets[i]->CurrentAttack = Targets[i]->CurrentAttack + _AttackBuff;
		Targets[i]->BaseDefense = Targets[i]->BaseDefense + _DefenseBuff;
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + _DefenseBuff;
		Targets[i]->AppliedAffects.push_back(CurrentAffect);
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
	delete CurrentAffect;
}

/* Wrapper function to debuff all souls in target vector for _AttackDebuff and _DefenseDebuff amounts and then
create Action object and check the next layer of effects.  */
void Card::SoulDebuff(vector<Soul*> Targets, Player * Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Debuff);
	Affect* CurrentAffect = new Affect(Card::_EffectType::Buff, this, ("-" + to_string(_AttackBuff) + "/-" + to_string(_DefenseBuff)));
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = Targets[i]->BaseAttack + _AttackDebuff;
		Targets[i]->CurrentAttack = Targets[i]->CurrentAttack + _AttackDebuff;
		Targets[i]->BaseDefense = Targets[i]->BaseDefense + _DefenseDebuff;
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + _DefenseDebuff;
		Targets[i]->AppliedAffects.push_back(CurrentAffect);
		this->Owner->CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
	delete CurrentAffect;
}
