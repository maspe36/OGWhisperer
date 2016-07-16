#include "stdafx.h"
#include "Hellspark_Mutt.h"

Hellspark_Mutt::~Hellspark_Mutt()
{
}

void Hellspark_Mutt::Effect(GameState* CurrentGame) {
	cout << CurrentGame->PlayersInGame[1]->Health << endl;
	CurrentGame->PlayersInGame[1]->Health = CurrentGame->PlayersInGame[1]->Health - 1;
	cout << CurrentGame->PlayersInGame[1]->Health << endl;
}