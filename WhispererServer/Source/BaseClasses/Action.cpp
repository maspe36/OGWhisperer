#include "Action.h"
#include "Player.h"
#include "Card.h"

Action::Action()
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

Action::Action(vector<Card*> CardTargets, vector<Player*> PlayerTargets, Player* Owner, _ActionType ActionType)
	: CardTargets(CardTargets), PlayerTargets(PlayerTargets), Owner(Owner), ActionType(ActionType)
{
}

Action::~Action()
{
}
