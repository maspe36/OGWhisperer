#include "Tavern_Hearth.h"
#include "Affect.h"

//Registrar registar("Tavern Hearth", Tavern_Hearth());
REGISTER_CLASS("Tavern Hearth", Tavern_Hearth);

Tavern_Hearth::Tavern_Hearth() 
	: Constant({ 0,0,3,0,0,0 }, "Tavern Hearth", "All red souls have +1/+0.", "When theres smoke theres fire!", _Color::Fire, _CardType::_Constant, { _EffectType::Introduce })
{
	_AttackBuff = 1;
	CardAffect = new Affect(Card::_EffectType::Buff, this, ("+" + to_string(_AttackBuff) + "/+" + to_string(_DefenseBuff)));
}

Tavern_Hearth::~Tavern_Hearth()
{
}

void Tavern_Hearth::Effect()
{
	// For all cards in the game
	for (auto i : Owner->CurrentGame->CardOrder) 
	{
		// For all their affects
		if (i->CardType == Card::_CardType::_Soul && i->Color == Card::_Color::Fire) 
		{
			bool IsAlreadyBuffed = false;

			for (auto a : i->AppliedAffects)
			{
				// If any of their affects DON'T match this cards
				if (a == CardAffect)
				{
					IsAlreadyBuffed = true;
				}
			}

			if (!IsAlreadyBuffed)
			{
				Soul* SoulCard = dynamic_cast<Soul*>(i);
				SoulBuffNoTrigger({ SoulCard }, Owner);
			}
		}
	}
}

bool Tavern_Hearth::IsEffectTriggered(Action* CurrentAction)
{
	// Was it a summon?
	if (CurrentAction->ActionType == Action::_ActionType::Summon)
	{
		// Check all cards being summoned, if any were a soul, red effect triggers
		for (auto i : CurrentAction->CardTargets)
		{
			// If it is this card
			if (i == this) {
				return true;
			}
			else if (i->CardType == Card::_CardType::_Soul && i->Color == Card::_Color::Fire) 
			{
				return true;
			}
		}
	}
	return false;
}
