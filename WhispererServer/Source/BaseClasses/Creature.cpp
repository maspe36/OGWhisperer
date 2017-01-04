#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "Creature.h"
#include "Player.h"
#include "Action.h"

Creature::Creature(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects, int OriginalAttack, int OriginalDefense) :
	Card(Cost, Name, FlavourText, EffectText, Color, CardType, Effects),
	OriginalAttack(OriginalAttack), OriginalDefense(OriginalDefense),
	BaseAttack(OriginalAttack), BaseDefense(OriginalDefense),
	CurrentAttack(OriginalAttack), CurrentDefense(OriginalDefense)
{
	CanAttack = false;
}

/* Reduces the flurry count and sets the CanAttack flag if they cannot attack this turn. */
void Creature::PreAttackMaintenance()
{
	// Make sure to reduce flurry (number of times a creature can attack in a turn)
	this->_Flurry = this->_Flurry - 1;

	if (this->_Flurry <= 0)
	{
		this->CanAttack = false;
	}
}

/* Applies damage to the target creature from the creature calling the function.
 Then the creature that called the function has damage applied to it equal to the
 target creature's current attack. If either creature's current defense is below zero
 the IsDead flag is set. Throws strings. */
void Creature::Attacking(Creature* DefendingCreature)
{
	// Were they summoned this turn?
	if (this->CanAttack)
	{
		// if they are not attacking their own creature or face...
		if (this->Owner != DefendingCreature->Owner)
		{
			// They can attack!
			PreAttackMaintenance();

			// Attack!
			DefendingCreature->CurrentDefense = DefendingCreature->CurrentDefense - CurrentAttack;
			CurrentDefense = CurrentDefense - DefendingCreature->CurrentAttack;
			if (DefendingCreature->CurrentDefense <= 0)
			{
				DefendingCreature->IsDead = true;
			}
			if (CurrentDefense <= 0)
			{
				IsDead = true;
			}

			// Set the CurrentAction object
			Action* CurrentAction = new Action(this, DefendingCreature, this->Owner, Action::_ActionType::Attack);
			this->Owner->CurrentGame->CheckEffects(CurrentAction);
			delete CurrentAction;

			cout << this->Owner->UserName << "'s " << this->Name << " attacked " << DefendingCreature->Owner->UserName << "'s " << DefendingCreature->Name << " for " << this->CurrentAttack << "!" << endl;
			cout << DefendingCreature->Owner->UserName << "'s " << DefendingCreature->Name << " has " << DefendingCreature->CurrentDefense << " health!" << endl;
			cout << this->Owner->UserName << "'s " << this->Name << " was hit for " << DefendingCreature->CurrentAttack << "!" << endl;
			cout << this->Owner->UserName << "'s " << this->Name << " has " << this->CurrentDefense << " health!" << endl;
		}
		else {
			throw "You cannot attack your own creatures!";
		}
	}
	else {
		// If they technically still have attacks but they can't attack, they were probably summoned this turn.
		if (_Flurry != 0) {
			throw this->Name + " cannot attack the turn it was summoned!";
		}
		else {
			throw this->Name + " cannot attack anymore this turn!";
		}
	}
}


/* Applies damage to the target player equal to creature that called this function's attack.
If the target players health is below 0 the IsDead flag is set. Throws strings.*/
void Creature::Attacking(Player* DefendingPlayer)
{
	// Were they summoned this turn?
	if (this->CanAttack)
	{
		// if they are not attacking their own creature or face...
		if (this->Owner != DefendingPlayer)
		{
			// They can attack!
			PreAttackMaintenance();

			// Attack!
			DefendingPlayer->Health = DefendingPlayer->Health - CurrentAttack;
			if (DefendingPlayer->Health <= 0)
			{
				DefendingPlayer->IsDead = true;
			}

			// Set CurrentAction object
			Action* CurrentAction = new Action(this, DefendingPlayer, this->Owner, Action::_ActionType::Attack);
			this->Owner->CurrentGame->CheckEffects(CurrentAction);
			delete CurrentAction;

			cout << this->Name << " attacked " << DefendingPlayer->UserName << " for " << this->CurrentAttack << "!" << endl;
			cout << DefendingPlayer->UserName << " has " << DefendingPlayer->Health << " health!" << endl;
		}
		else {
			throw "You cannot attack your yourself!";
		}
	}
	else {
		// If they technically still have attacks but they can't attack, they were probably summoned this turn.
		if (_Flurry != 0) {
			throw this->Name + " cannot attack the turn it was summoned!";
		}
		else {
			throw this->Name + " cannot attack anymore this turn!";
		}
	}
}
