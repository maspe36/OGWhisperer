#include "Spark_Mouse.h"
#include <sstream>
#include "Action.h"
#include "CardUtility.h"

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
	if (CardUtility::IsColorSoulPresent(this->Owner->CurrentGame, this->Color))
	{
		vector<string> Parts = CardUtility::GetUserSoulTarget();
		try 
		{
			// Grab the frist char from the string (only char)
			string TargetType = Parts[0];
			int PlayerIndex = stoi(Parts[1]);
			int SoulIndex = stoi(Parts[2]);

			if (TargetType[0] == this->Owner->CurrentGame->SoulProto) // Soul target
			{
				SoulBuff({ this->Owner->CurrentGame->PlayersInGame[PlayerIndex]->SoulsInPlay[SoulIndex] }, Owner);
			}
			else // Invalid input, try again.
			{
				Effect();
			}
		} // We don't really care what happened here. We will call this recursively anyway. 
		catch (...) // maybe one day this will need to be changed.
		{
			Effect();
		}

	}
	else
	{
		cout << "No acceptable targets!" << endl;
	}
}

bool Spark_Mouse::IsEffectTriggered(Action* CurrentAction)
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
