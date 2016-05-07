#include "stdafx.h"
#include "GameState.h"
#include <string>

GameState::GameState(Player* newPlayer1, Player* newPlayer2)
{
	player1 = newPlayer1;
	player2 = newPlayer2;
}

GameState::~GameState()
{
	delete player1;
	delete player2;
}

void GameState::Start() {
	bool IsPlayer1Turn = true;

	//While both players have more than 0 health
	while (player1->Health > 0 && player2->Health > 0)
	{
		//Player 1 turn loop
		//Player 1 Draw
		while (IsPlayer1Turn)
		{
			//Should be a message recieved in plain text from the client
			string MessageFromClient = "1:Example";
			char Protocol = MessageFromClient[0];
			switch (Protocol) {
			case '1':
				string CardFromClientInfo = MessageFromClient.substr(2);
			  /*Soul* CardFromClient = Factory.CreateCard(CardFromClientInfo);
				if(player1->IsCardInHand(CardFromClient))
				{
					if(player1->IsCardPlayable(CardFromClient))
					{
						player1->SoulsInPlay.Add(CardFromClient);
					}
				}*/
				break;
			}
			//Check effects
		}
		//Player 2 turn loop
		//Player 1 Draw
		while (!IsPlayer1Turn)
		{

		}
	}
}

string GameState::ToString(Player* ActivePlayer)
{
	//GameState?
	//Player1=PlayerName+PlayerHealth
	//&Player1SoulsInPlay=SoulName+SoulCost+SoulDescription#...
	//&PlayerConstantsInPlay=ConstantName+ConstantCost+ConstantDescription#...
	//&Player1CountOfDeck=CountOfDeck
	return "Player1=" + player1->ToString() +
		"&Player1SoulsInPlay=" + player1->SoulsInPlayToString() +
		"&Player1DeckCount=" + to_string(player1->MainDeck.Cards.size()) +
		"&Player2=" + player2->ToString() +
		"&Player2SoulsInPlay=" + player2->SoulsInPlayToString() +
		"&Player2DeckCount=" + to_string(player2->MainDeck.Cards.size()) +
		"&ActivePlayerHand=" + ActivePlayer->HandToString();
}




