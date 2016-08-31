#include "stdafx.h"
#include <string>
#include "Card.h"
#include "Soul.h"
#include "Player.h"
#include "Action.h"
#include "GameState.h"

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

void Card::Damage(vector<Soul*> Targets, GameState* CurrentGame, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Damage);

	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense - this->_Damage;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " took " << _Damage << " damage!" << endl;
		cout << Targets[i]->Name << " has " << Targets[i]->CurrentDefense << " health!" << endl;
		// Set the dead flag if the card is dead
		if (Targets[i]->CurrentDefense < 0) 
		{
			Targets[i]->IsDead = true;
		}
		CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

void Card::Damage(vector<Player*> Targets, GameState* CurrentGame, Player* Owner)
{
	Action* CurrentAction = new Action(Targets, Owner, Action::_ActionType::Damage);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health - this->_Damage;
		cout << Targets[i]->UserName << " lost " << _Damage << " health!" << endl;
		cout << Targets[i]->UserName << " has " << Targets[i]->Health << " health!" << endl;
		CurrentGame->CheckEffects(CurrentAction);
		// Set the dead flag if they are dead
		if (Targets[i]->Health < 0)
		{
			Targets[i]->IsDead = true;
		}
	}
	delete CurrentAction;
}

void Card::Heal(vector<Soul*> Targets, GameState* CurrentGame, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::Heal);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->CurrentDefense = Targets[i]->CurrentDefense + this->_Heal;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " healed for " << _Heal << endl;
		cout << Targets[i]->Name << " has " << Targets[i]->CurrentDefense << " health!" << endl;
		CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

void Card::Heal(vector<Player*> Targets, GameState* CurrentGame, Player* Owner)
{
	Action* CurrentAction = new Action(Targets, Owner, Action::_ActionType::Heal);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->Health = Targets[i]->Health + this->_Heal;
		cout << Targets[i]->UserName << " healed for " << _Heal << endl;
		cout << Targets[i]->UserName << " has " << Targets[i]->Health << " health!" << endl;
		CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

void Card::AttackChange(vector<Soul*> Targets, GameState* CurrentGame, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::AttackChange);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseAttack = this->_AttackChange;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " had its attack set to " << _AttackChange << endl;
		CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}

void Card::DefenseChange(vector<Soul*> Targets, GameState* CurrentGame, Player* Owner)
{
	vector<Card*> tmpCardTargets(Targets.begin(), Targets.end());
	Action* CurrentAction = new Action(tmpCardTargets, Owner, Action::_ActionType::DefenseChange);
	for (size_t i = 0; i < Targets.size(); i++) {
		Targets[i]->BaseDefense = this->_DefenseChange;
		cout << Targets[i]->Owner->UserName << "'s " << Targets[i]->Name << " had its defense set to " << _DefenseChange << endl;
		CurrentGame->CheckEffects(CurrentAction);
	}
	delete CurrentAction;
}