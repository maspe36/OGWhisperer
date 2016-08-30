#include "stdafx.h"
#include "Hellspark_Mutt.h"
#include <boost/algorithm/string.hpp>
#include <sstream>

Hellspark_Mutt::Hellspark_Mutt()
	: Soul({ 0,0,3,0,0,0 }, "Hellspark Mutt", "Introduce - Deal 1 damage to target soul or player.", "", _Color::Fire, _CardType::_Soul, { _EffectType::Introduce }, 3, 2)
{
	_Damage = 1;
}

Hellspark_Mutt::~Hellspark_Mutt()
{
}

void Hellspark_Mutt::Effect(GameState* CurrentGame)
{
	Action* CurrentAction = new Action;
	CurrentAction->ActionType = Action::_ActionType::Damage;
	CurrentAction->Owner = Owner;

	cout << "Select a target..." << endl;
	// Now we take input and depending on what it is set action object.
	string ClientInput;
	getline(cin, ClientInput);
	
	vector<string> Parts;

	boost::split(Parts, ClientInput, boost::is_any_of(CurrentGame->delemiter));

	// Grab the frist char from the string (only char)
	char TargetType = ClientInput[0];
	int PlayerIndex = stoi(Parts[1]);

	if (TargetType == CurrentGame->PlayerProto) // Player Target
	{
		CurrentGame->PlayersInGame[PlayerIndex]->Health 
			= CurrentGame->PlayersInGame[PlayerIndex]->Health - 1;
		cout << CurrentGame->PlayersInGame[PlayerIndex]->UserName << " lost " << 1 << " health!" << endl;
		cout << CurrentGame->PlayersInGame[PlayerIndex]->UserName << " has " << CurrentGame->PlayersInGame[PlayerIndex]->Health << endl;
		// The effect was a success!
		CurrentGame->CheckEffects(CurrentAction);
	}
	else if (TargetType == CurrentGame->SoulProto) // Soul target
	{
		int SoulIndex = stoi(Parts[2]);
		CurrentGame->PlayersInGame[PlayerIndex]->SoulsInPlay[SoulIndex]->CurrentDefense 
			= CurrentGame->PlayersInGame[PlayerIndex]->SoulsInPlay[SoulIndex]->CurrentDefense - 1;
		// The effect was a success!
		CurrentGame->CheckEffects(CurrentAction);
	}
	else // Return it to the hand if the user gives invalid target input 
	{

	}

	delete CurrentAction;
}

bool Hellspark_Mutt::IsEffectTriggered(Action* CurrentAction)
{
	// If this card was summoned
	if (CurrentAction->_ActionType::Summon) {
		for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
		{
			if (CurrentAction->CardTargets[i] == this) {
				return true;
			}
		}
	}
	return false;
}
