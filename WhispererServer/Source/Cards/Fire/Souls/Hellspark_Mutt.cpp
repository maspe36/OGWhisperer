#include "stdafx.h"
#include "Hellspark_Mutt.h"
#include <sstream>

Hellspark_Mutt::Hellspark_Mutt()
	: Soul({ 0,0,3,0,0,0 }, "Hellspark Mutt", "Introduce - Deal 1 damage to target soul or player.", "", _Color::Fire, _CardType::Soul, { _EffectType::Introduce }, 3, 2)
{
}

Hellspark_Mutt::~Hellspark_Mutt()
{
}

void Card::Effect(GameState* CurrentGame)
{
	Action* CurrentAction = new Action;
	CurrentAction->ActionType = Action::_ActionType::Damage;
	CurrentAction->Owner = Owner;

	// Now we take input and depending on what it is set action object.
	string input;
	getline(cin, input);

	// Remove delimiter character and replace it with space
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ':')
			input[i] = ' ';
	}

	// Split the string and store the contents 
	vector<int> Parts;
	stringstream Spliter(input);
	int temp;
	while (Spliter >> temp) {
		Parts.push_back(temp);
	}

	int type = Parts[0];
	int owner = Parts[1];
	int target = Parts[2];

	if (type == 0) {
		Player* targetPlayer = CurrentGame->PlayersInGame[target];
		CurrentAction->PlayerTargets.push_back(targetPlayer);
	}
	else {
		Card* targetCard = CurrentGame->PlayersInGame[owner]->SoulsInPlay[target];
		CurrentAction->CardTargets.push_back(targetCard);
	}
	CurrentGame->CheckEffects(CurrentAction);
	delete CurrentAction;
}

bool Card::IsEffectTriggered(Action* CurrentAction)
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
