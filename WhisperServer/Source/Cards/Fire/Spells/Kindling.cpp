#include "Kindling.h"
#include "CardUtility.h"

REGISTER_CLASS("Kindling", Kindling);

Kindling::Kindling()
	: Spell({ 0,0,1,0,0,0 }, "Kindling", "Deal 2 damage to target player or creature.", "A single spark can set a world ablaze.", _Color::Fire, _CardType::_Spell, { _EffectType::Introduce })
{
	_Damage = 2;
}

Kindling::~Kindling()
{
}

void Kindling::Effect()
{
	vector<string> Parts = CardUtility::GetUserCreatureOrPlayerTarget();

	try {
		// Grab the frist char from the string (only char)
		string TargetType = Parts[0];
		int PlayerIndex = stoi(Parts[1]);

		if (TargetType[0] == Owner->CurrentGame->PlayerProto) // Player Target
		{
			Damage({ Owner->CurrentGame->PlayersInGame[PlayerIndex] }, Owner);
		}
		else if (TargetType[0] == Owner->CurrentGame->CreatureProto) // Creature target
		{
			int CreatureIndex = stoi(Parts[2]);
			Damage({ Owner->CurrentGame->PlayersInGame[PlayerIndex]->CreaturesInPlay[CreatureIndex] }, Owner);
		}
		else {
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

	// Because it is a spell its dead once the effect triggers.
	IsDead = true;
}

bool Kindling::IsEffectTriggered(Action * CurrentAction)
{
	// If this card was played
	if (CurrentAction->ActionType == Action::_ActionType::Summon) 
	{
		for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
		{
			if (CurrentAction->CardTargets[i] == this) 
			{
				return true;
			}
		}
	}
	return false;
}
