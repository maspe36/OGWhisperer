#include "stdafx.h"
#include <string>
#include <vector>
#include "Cards.h"
#include "GameState.h"
#include "Player.h"

int main()
{
	//I want a factory...
	//How should I do this part? This seems complex
	//I could do the CardFactory method where I create a new Card* from the specific cards class
	//Then it fits into my game structure

	Fire_Spirit *firespirit1 = new Fire_Spirit();
	Fire_Spirit *firespirit2 = new Fire_Spirit();

	Pyromaniac *pyromaniac1 = new Pyromaniac();
	Pyromaniac *pyromaniac2 = new Pyromaniac();

	Hellhound *hellhound1 = new Hellhound();
	Hellhound *hellhound2 = new Hellhound();

	Hellspark_Mutt *hellsparkmutt1 = new Hellspark_Mutt();
	Hellspark_Mutt *hellsparkmutt2 = new Hellspark_Mutt();

	vector<Card*> genericDeck;
	genericDeck.push_back(firespirit1);
	genericDeck.push_back(firespirit2);

	genericDeck.push_back(pyromaniac1);
	genericDeck.push_back(pyromaniac2);

	genericDeck.push_back(hellhound1);
	genericDeck.push_back(hellhound2);

	genericDeck.push_back(hellsparkmutt1);
	genericDeck.push_back(hellsparkmutt2);

	// New players need a deck and a name
	Player* player1 = new Player("Sam", genericDeck);
	Player* player2 = new Player("Ben", genericDeck);
	Player* player3 = new Player("Nick", genericDeck);

	vector<Player*> Players = { player1, player2, player3 };

	GameState* myGame = new GameState(Players);

	myGame->Start();

	//// Attack the player with the first soul in play

	//// This will be sent along with the message from the client as to who to declare an attack on
	//int PlayerIndexToBeAttacked = 1;
	//int AttackingSoulIndex = 0;
	//myGame->ActivePlayer->SoulsInPlay.at
	//	(AttackingSoulIndex)->Attacking(myGame->PlayersInGame[PlayerIndexToBeAttacked]);

	//cout << myGame->ActivePlayer->SoulsInPlay.at
	//	(AttackingSoulIndex)->Name + " attacked " + myGame->PlayersInGame
	//		[PlayerIndexToBeAttacked]->UserName + " for " + to_string(myGame->ActivePlayer->SoulsInPlay.at(0)->Attack) << endl;

	return 0;
}
