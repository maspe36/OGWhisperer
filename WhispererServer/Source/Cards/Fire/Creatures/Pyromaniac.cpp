#include "Pyromaniac.h"
#include "CardUtility.h"

REGISTER_CLASS("Pyromaniac", Pyromaniac);

Pyromaniac::Pyromaniac()
	: Creature({ 0,0,4,0,0,0 }, "Pyromaniac", "", "Downfall - Deal 2 damage to target player or creature", _Color::Fire, _CardType::_Creature, { _EffectType::Downfall }, 3, 4)
{
	_Damage = 2;
}

Pyromaniac::~Pyromaniac()
{
}

void Pyromaniac::Effect()
{
	vector<string> Parts = CardUtility::GetUserCreatureOrPlayerTarget();

	try
	{
		// Grab the frist char from the string (only char)
		string TargetType = Parts.at(0);
		int PlayerIndex = stoi(Parts.at(1));

		if (TargetType.at(0) == Owner->CurrentGame->PlayerProto) // Player Target
		{
			Damage({ Owner->CurrentGame->PlayersInGame.at(PlayerIndex) }, Owner);
		}
		else if (TargetType.at(0) == Owner->CurrentGame->CreatureProto) // Creature target
		{
			int CreatureIndex = stoi(Parts.at(2));
			Damage({ Owner->CurrentGame->PlayersInGame.at(PlayerIndex)->CreaturesInPlay.at(CreatureIndex) }, Owner);
		}
		else // Invalid input, try again.
		{
			cout << "Invalid input!" << endl;
			Effect();
		}
	}// target doesn't exits
	catch (const out_of_range& e) {
		cout << "That target doesn't exist!" << endl;
		Effect();
	}
	catch (...) // All else fails
	{
		cout << "Something went wrong!" << endl;
		Effect();
	}
}

bool Pyromaniac::IsEffectTriggered(Action* CurrentAction)
{
	// If this card is destroyed
	if (CurrentAction->ActionType == Action::_ActionType::Destroy)
	{
		for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
		{
			if (CurrentAction->CardTargets.at(i) == this) {
				return true;
			}
		}
	}
	return false;
}

