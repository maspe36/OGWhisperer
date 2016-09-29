#include "Spark_Mouse.h"
#include <sstream>
#include "CardUtility.h"

REGISTER_CLASS("Spark Mouse", Spark_Mouse);

Spark_Mouse::Spark_Mouse()
	: Soul({ 0,0,1,0,0,0 }, "Spark Mouse", "Introduction - Give a red soul ", "", _Color::Fire, _CardType::_Soul, { _EffectType::Buff }, 1, 1)
{
	_AttackBuff = 1;
	_DefenseBuff = 1;
	stringstream os;
	os << "+" << _AttackBuff << "/+" << _DefenseBuff;
	EffectText = EffectText + os.str();
}


Spark_Mouse::~Spark_Mouse()
{
}

void Spark_Mouse::Effect()
{

	vector<string> Parts = CardUtility::GetUserSoulTarget();
	try
	{
		// Grab the frist char from the string (only char)
		string TargetType = Parts.at(0);
		int PlayerIndex = stoi(Parts.at(1));
		int SoulIndex = stoi(Parts.at(2));

		if (TargetType.at(0) == Owner->CurrentGame->SoulProto) // Soul target
		{
			SoulBuff({ Owner->CurrentGame->PlayersInGame.at(PlayerIndex)->SoulsInPlay.at(SoulIndex) }, Owner);
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

bool Spark_Mouse::IsEffectTriggered(Action* CurrentAction)
{
	// If this card was summoned
	if (CurrentAction->ActionType == Action::_ActionType::Summon)
	{
		if (CardUtility::IsColorSoulPresent(Owner->CurrentGame, Color))
		{
			for (size_t i = 0; i < CurrentAction->CardTargets.size(); i++)
			{
				if (CurrentAction->CardTargets[i] == this)
				{
					return true;
				}
			}
		}
	}
	return false;
}
