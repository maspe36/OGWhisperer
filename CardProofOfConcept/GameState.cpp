#include "stdafx.h"
#include "GameState.h"
#include <string>

GameState::GameState(Player* newPlayer1, Player* newPlayer2)
{
	PlayersInGame.push_back(newPlayer1);
	PlayersInGame.push_back(newPlayer2);
}

GameState::~GameState()
{
	//For every player in the game, 
	//delete their pointers stored here when the game ends.
	for (Player* i : PlayersInGame) {
		delete i;
	}
}

string GameState::ToString(Player* RecivingGameStatePlayer)
{
	//GameState?
	//Player1=PlayerName+PlayerHealth
	//&Player1SoulsInPlay=SoulName+SoulCost+SoulDescription#...
	//&PlayerConstantsInPlay=ConstantName+ConstantCost+ConstantDescription#...
	//&Player1CountOfDeck=CountOfDeck

	//! = player info is starting
	//& = continuation of player info from the !
	//# = seperates multiple cards returned in a section of the player info (ex. SoulsInPlay) 

	//for each player in vector<player*>, print their souls, constants, deck and hand counts. Send the active player their hand
	string GameStateInfo = "GameState?";
	for (int i = 0; i < PlayersInGame.size; i++) {
		GameStateInfo +=
			"!Player" + to_string(i) + "=" + PlayersInGame[i]->ToString() +
			"&Player" + to_string(i) + "SoulsInPlay=" + PlayersInGame[i]->SoulsInPlayToString() +
			//"&Player" + to_string(i) + "ConstantsInPlay=" + PlayersInGame[i]->ConstantsInPlayToString() +
			//"&Player" + to_string(i) + "SwiftsInPlay=" + PlayersInGame[i]->SwiftsInPlayToString() +
			"&Player" + to_string(i) + "DeckCount=" + to_string(PlayersInGame[i]->MainDeck.Cards.size());
			"&Player" + to_string(i) + "HandCount=" + to_string(PlayersInGame[i]->Hand.size());
	}
	//Print all cards in active players hand if they are the active player
	if (RecivingGameStatePlayer == ActivePlayer) {
		GameStateInfo += 
			"&ActivePlayerHand=" + ActivePlayer->HandToString();
	}
	return GameStateInfo;
}

void GameState::ChangeActivePlayer() {
	//If the active player is the last item in the vector
	if (ActivePlayer == PlayersInGame.back()) {
		//Set it to the front of the vector
		ActivePlayer = PlayersInGame.front();
	}
	else {
		//Find the index of the current active player
		int IndexOfActivePlayer = distance(PlayersInGame.begin(), find(PlayersInGame.begin(), PlayersInGame.end(), 3));
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

