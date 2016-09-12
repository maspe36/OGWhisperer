#include "stdafx.h"
#include "Hellspark_Mutt.h"
#include <sstream>
#include "CardUtility.h"

Hellspark_Mutt::Hellspark_Mutt()
	: Soul({ 0,0,3,0,0,0 }, "Hellspark Mutt", "", "Introduce - Deal 1 damage to target soul or player.", _Color::Fire, _CardType::_Soul, { _EffectType::Introduce }, 3, 2)
{
	_Damage = 1;
}

Hellspark_Mutt::~Hellspark_Mutt()
{
}

void Hellspark_Mutt::Effect()
{
	vector<string> Parts = CardUtility::GetUserSoulOrPlayerTarget();

	// Grab the frist char from the string (only char)
	string TargetType = Parts[0];
	int PlayerIndex = stoi(Parts[1]);

	if (TargetType[0] == Owner->CurrentGame->PlayerProto) // Player Target
	{
		Damage({ Owner->CurrentGame->PlayersInGame[PlayerIndex] }, Owner);
	}
	else if (TargetType[0] == Owner->CurrentGame->SoulProto) // Soul target
	{
		int SoulIndex = stoi(Parts[2]);
		Damage({ Owner->CurrentGame->PlayersInGame[PlayerIndex]->SoulsInPlay[SoulIndex] }, Owner);
	}
	else // Return it to the hand if the user gives invalid target input 
	{

	}
}

bool Hellspark_Mutt::IsEffectTriggered(Action* CurrentAction)
{
	// If this card was summoned
	if (CurrentAction->ActionType == Action::_ActionType::Summon) {
		for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
		{
			if (CurrentAction->CardTargets[i] == this) {
				return true;
			}
		}
	}
	return false;
}
