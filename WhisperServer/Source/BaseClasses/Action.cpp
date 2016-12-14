#include "Action.h"
#include "Player.h"
#include "Card.h"

Action::Action()
{
}

Action::Action(Player * Owner, _ActionType ActionType) 
	: Owner(Owner), ActionType(ActionType)
{
}

Action::Action(vector<Card*> CardTargets, Player* Owner, _ActionType ActionType)
	: CardTargets(CardTargets), Owner(Owner), ActionType(ActionType)
{
}

Action::Action(vector<Player*> PlayerTargets, Player* Owner, _ActionType ActionType)
	: PlayerTargets(PlayerTargets), Owner(Owner), ActionType(ActionType)
{
}

Action::Action(Creature * Attacker, Creature * Target, Player * Owner, _ActionType ActionType) 
	: Attacker(Attacker), Target(Target), Owner(Owner), ActionType(ActionType)
{
}

Action::Action(Creature * Attacker, Player * PlayerTarget, Player * Owner, _ActionType ActionType)
	: Attacker(Attacker), PlayerTarget(PlayerTarget), Owner(Owner), ActionType(ActionType)
{
}

Action::Action(vector<Card*> CardTargets, vector<Player*> PlayerTargets, Player* Owner, _ActionType ActionType)
	: CardTargets(CardTargets), PlayerTargets(PlayerTargets), Owner(Owner), ActionType(ActionType)
{
}

Action::~Action()
{
}
