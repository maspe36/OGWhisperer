#include "stdafx.h"
#include "Pyromaniac.h"
#include <boost/algorithm/string.hpp>
#include <sstream>

Pyromaniac::Pyromaniac() 
	: Soul({ 0,0,4,0,0,0 }, "Pyromaniac", "", "Downfall - Deal 2 damage to target player or soul", _Color::Fire, _CardType::_Soul, { _EffectType::Downfall }, 3, 4)
{
	_Damage = 2;
}

Pyromaniac::~Pyromaniac()
{
}

void Pyromaniac::Effect()
{
	cout << "Select a target..." << endl;
	// Now we take input and depending on what it is set action object.
	string ClientInput;
	getline(cin, ClientInput);

	vector<string> Parts;

	boost::split(Parts, ClientInput, boost::is_any_of(this->Owner->CurrentGame->delemiter));

	// Grab the frist char from the string (only char)
	char TargetType = ClientInput[0];
	int PlayerIndex = stoi(Parts[1]);

	if (TargetType == this->Owner->CurrentGame->PlayerProto) // Player Target
	{
		Damage({ this->Owner->CurrentGame->PlayersInGame[PlayerIndex] }, Owner);
	}
	else if (TargetType == this->Owner->CurrentGame->SoulProto) // Soul target
	{
		int SoulIndex = stoi(Parts[2]);
		Damage({ this->Owner->CurrentGame->PlayersInGame[PlayerIndex]->SoulsInPlay[SoulIndex] }, Owner);
	}
	else // Return it to the hand if the user gives invalid target input 
	{

	}
}

bool Pyromaniac::IsEffectTriggered(Action* CurrentAction)
{
	// If this card is destroyed
	if (CurrentAction->ActionType == Action::_ActionType::Destroy)
	{
		for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
		{
			if (CurrentAction->CardTargets[i] == this) {
				return true;
			}
		}
	}
	return false;
}

