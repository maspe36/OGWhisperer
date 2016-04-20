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




