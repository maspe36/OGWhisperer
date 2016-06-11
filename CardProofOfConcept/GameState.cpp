#include "stdafx.h"
#include "GameState.h"
#include <string>

GameState::GameState(vector<Player*> Players)
{
	// Set our players in the game equal to the inserted vector of players entering the game
	PlayersInGame = Players;

	// Initialize ActivePlayer
	// This determines who goes first, we need to make it random whoever goes first
	// For now we can just let the first player in the vector go first
	ActivePlayer = PlayersInGame[0];
}

GameState::~GameState()
{
	//For every player in the game, 
	//delete their pointers stored here when the game ends.
	for (Player* i : PlayersInGame) {
		delete i;
	}
}

void GameState::ChangeActivePlayer() {
	//If the active player is the last item in the vector
	if (ActivePlayer->Compare(PlayersInGame.back())) {
		//Set it to the front of the vector
		ActivePlayer = PlayersInGame.front();
	}
	else {
		//Find the index of the current active player
		int IndexOfActivePlayer = find(PlayersInGame.begin(), PlayersInGame.end(), ActivePlayer) - PlayersInGame.begin();
		//Go one past it
		ActivePlayer = PlayersInGame[IndexOfActivePlayer + 1];
	}
}

void GameState::StartOfTurnEffects() {
	ActivePlayer->DrawCard();
	//ActivePlayer->RefillDevotion();
}

void GameState::Start() {
	bool IsGameLive = true;

	//While the game is ongoing or 'live'
	while (IsGameLive)
	{
		//Should be a message recieved in plain text from the client
		string MessageFromClient = "1:Example";
		char Protocol = MessageFromClient[0];
		string CardFromClientInfo = MessageFromClient.substr(2);

		//CURRENT PROTOCOL
		//s = soul entering play
		//c = constant entering play
		//w = swift entering play
		//e = end of active players turn

		switch (Protocol) {
		case 's':
			/*Soul* CardFromClient = Factory.CreateCard(CardFromClientInfo);
			  if(ActivePlayer->IsCardInHand(CardFromClient))
			  {
				  if(ActivePlayer->IsCardPlayable(CardFromClient))
				  {
					  ActivePlayer->SoulsInPlay.Add(CardFromClient);
				  }
			  }*/
			break;
		case 'e':
			//Active player changes from the active player that entered the switch here
			ChangeActivePlayer();
			//The now active player needs to draw and have their mana refilled
			break;

		}
		//Check effects
	}
}

