// CardProofOfConcept.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include "Cards.h"
#include "GameState.h"

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

	//cout << "Cost: " + to_string(firespirit1->Cost) + '\n'
	//	<< "Name: " + firespirit1->Name + '\n'
	//	<< "Description: " + firespirit1->Description + '\n'
	//	<< "Attack: " + to_string(firespirit1->Attack) + '\n'
	//	<< "Defense: " + to_string(firespirit1->Defense) + '\n' << endl;

	//cout << "Cost: " + to_string(pyromaniac1->Cost) + '\n'
	//	 << "Name: " + pyromaniac1->Name + '\n'
	//	 << "Description: " + pyromaniac1->Description + '\n'
	//	 << "Attack: " + to_string(pyromaniac1->Attack) + '\n'
	//	 << "Defense: " + to_string(pyromaniac1->Defense) + '\n' << endl;

	////Some bizzare behaviour when adding a char to the end of a string
	////Im new to c++ okay
	//cout << "Fire Spirit attacks Pyromaniac!\n" << endl;
	//firespirit1->Soul::Attacking(pyromaniac1);

	//cout << "Cost: " + to_string(pyromaniac1->Cost) + '\n'
	//	<< "Name: " + pyromaniac1->Name + '\n'
	//	<< "Description: " + pyromaniac1->Description + '\n'
	//	<< "Attack: " + to_string(pyromaniac1->Attack) + '\n'
	//	<< "Defense: " + to_string(pyromaniac1->Defense) + '\n' << endl;

	//cout << SoulCard->Name << " is attacking " << player2->UserName << " for " << SoulCard->Attack << "!" << endl;
	//SoulCard->Attacking(player2);
	//cout << player2->Health << endl;


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
	Player* player1 = new Player(genericDeck, "Maspe36");
	Player* player2 = new Player(genericDeck, "ScottSterling");

	vector<Player*> Players = { player1, player2 };

	GameState* myGame = new GameState(Players);

	// Draw a card and add it to the players hand
	myGame->ActivePlayer->DrawCard();
	myGame->ActivePlayer->DrawCard();
	myGame->ActivePlayer->DrawCard();
	cout << myGame->ActivePlayer->HandToString() << endl;

	// Print GameState
	// cout << myGame->ToString(myGame->ActivePlayer) << endl;

	// Make a wrapper method?
	// Play card at index in hand
	int CardToPlay;
	cin >> CardToPlay;
	myGame->PlayCard(myGame->ActivePlayer, CardToPlay);
	cout << myGame->ActivePlayer->HandToString() << endl;

	// Attempt to activate mutt's effect
	myGame->ActivePlayer->SoulsInPlay.at(0)->Effect(myGame);
	
	// Make a wrapper method?
	// Attack the player with the first soul in play

	// This will be sent along with the message from the client as to who to declare an attack on
	int PlayerIndexToBeAttacked = 1;
	int AttackingSoulIndex = 0;
	myGame->ActivePlayer->SoulsInPlay.at
		(AttackingSoulIndex)->Attacking(myGame->PlayersInGame[PlayerIndexToBeAttacked]);

	cout << myGame->ActivePlayer->SoulsInPlay.at
		(AttackingSoulIndex)->Name + " attacked " + myGame->PlayersInGame
			[PlayerIndexToBeAttacked]->UserName + " for " + to_string(myGame->ActivePlayer->SoulsInPlay.at(0)->Attack) << endl;

	// cout << myGame.player2->UserName << " has " << myGame.player2->Health << " remaining!" << endl;
	// cout << myGame->ToString(myGame->ActivePlayer) << endl;

	delete myGame;

    return 0;
}

