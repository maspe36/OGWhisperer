#include "Constant.h"
#include "Affect.h"

#include <string>
#include <sstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

Constant::Constant(vector<int> Cost, string Name, string FlavourText, string EffectText, _Color Color, _CardType CardType, vector<_EffectType> Effects)
	: Card(Cost, Name, FlavourText, EffectText, Color, CardType, Effects)
{
}


Constant::~Constant()
{
}

/* Remove all affects of a constant. This can be from creatures etc. */
void Constant::IsDeadMaintenance()
{
	try
	{
		for (auto p : Owner->CurrentGame->PlayersInGame) 
		{
			for (auto s : p->CreaturesInPlay) 
			{
				RemoveEffect(s);
			}
		}
	}
	catch (const out_of_range& e) {
		cout << "Can't find a target to remove effects from!" << endl;
	}
	catch (...)
	{
		cout << "Something went wrong!" << endl;
	}
}

void Constant::RemoveEffect(Card* Target)
{
	Affect* affect;
	for (auto a : Target->AppliedAffects) 
	{
		if (a == CardAffect)
		{
			affect = a;
		}
	}
	Target->AppliedAffects.erase(
		remove(Target->AppliedAffects.begin(), Target->AppliedAffects.end(), affect),
		Target->AppliedAffects.end());

	// Remove the buffs from the card itself
	if (Creature* CreatureCard = dynamic_cast<Creature*>(Target)) 
	{
		CreatureCard->CurrentAttack = CreatureCard->CurrentAttack - _AttackBuff;
		CreatureCard->CurrentAttack = CreatureCard->CurrentAttack + _AttackDebuff;
		CreatureCard->CurrentDefense = CreatureCard->CurrentDefense - _DefenseBuff;
		CreatureCard->CurrentDefense = CreatureCard->CurrentDefense + _DefenseDebuff;
	}
}
