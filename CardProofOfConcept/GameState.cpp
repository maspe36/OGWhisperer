#include "stdafx.h"
#include <string>
#include <sstream>
#include "BaseClasses.h"

GameState::GameState(vector<Player*> Players) : PlayersInGame(Players)
{
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

void GameState::PlayCard(Player* CardOwner, int HandIndex)
{
	Card *FromHand = CardOwner->Hand.at(HandIndex);

	Soul *SoulCard = nullptr;
	//Type2 *t2 = nullptr;
	//Type3 *t3 = nullptr;

	if (SoulCard = dynamic_cast<Soul*>(FromHand))
	{
		// Logically put the card in play
		CardOwner->SoulsInPlay.push_back(SoulCard);
		// Declare it has entered play
		cout << SoulCard->Name << " has entered the field for " << CardOwner->UserName << endl;
		// Remove the card from the hand if it succesfully enters the field
		CardOwner->Hand.erase(CardOwner->Hand.begin() + HandIndex);
		// Add the card to the stack
		Stack.push_back(SoulCard);
	}
	// if (t2 = dynamic_cast<Type2*>(p))
	//{
	//t2->type2Method();
	//}
	//else if (t3 = dynamic_cast<Type3*>(p))
	//{
	//t3->type3Method();
	//}
}

void GameState::Start() {
	bool IsGameLive = true;
	bool IsMulliganState = true;
	int MaxPlayerKeeps = PlayersInGame.size();
	int PlayersThatKept = 0;

	cout << "Begin Mulligans!" << endl;
	cout << endl;

	for (int i = 0; i < PlayersInGame.size(); i++) {
		// Draw 5 cards before the game starts
		PlayersInGame[i]->DrawCard(5);
	}

	while (IsMulliganState) {
		cout << "Max Player Keeps: " << MaxPlayerKeeps << endl;
		cout << "Players Keeping: " << PlayersThatKept << endl;
		cout << endl;

		// Show them the cards
		for (int i = 0; i < PlayersInGame.size(); i++) {
			cout << PlayersInGame[i]->UserName << endl;
			cout << PlayersInGame[i]->HandToString() << endl;
		}
			
		// Get the user input
		// UserIndex	:	IsMulligan
		// Parts[0]		:	Parts[1]
		string Choice;
		getline(cin, Choice);

		// Remove delimiter character and replace it with space
		for (int i = 0; i < Choice.length(); i++)
		{
			if (Choice[i] == ':')
				Choice[i] = ' ';
		}

		// Split the string and store the contents 
		vector<int> Parts;
		stringstream Spliter(Choice);
		int temp;
		while (Spliter >> temp) {
			Parts.push_back(temp);
		}

		int Index = Parts[0];
		int IsMulligan = Parts[1];

		// They want to mulligan
		if (IsMulligan == 1) {
			// Have they mulliganed too many times?
			if (PlayersInGame[Index]->MulligansTaken >= 5) {
				PlayersInGame[Index]->KeepHand = true;
				PlayersThatKept++;
				break;
			}
			// Begin mulligan logic
			else {
				// Increase the mulligan counter
				PlayersInGame[Index]->MulligansTaken = (PlayersInGame[Index]->MulligansTaken + 1);
				// Return their hand to the deck
				PlayersInGame[Index]->HandToDeck();
				// Draw 5 cards minus the amount of mulligans taken!
				PlayersInGame[Index]->DrawCard(5 - PlayersInGame[Index]->MulligansTaken);
			}
		}
		// They want to keep
		else {
			PlayersInGame[Index]->KeepHand = true;
			PlayersThatKept++;
		}

		// If every player has decided to keep, we are done mulliganning
		if (PlayersThatKept == MaxPlayerKeeps) {
			IsMulliganState = false;
		}
	}
	cout << "End Mulligans..." << endl;
	cout << endl;
	cout << "Start Game!" << endl;

	//While the game is ongoing or 'live'
	while (IsGameLive)
	{
		// Should be a message recieved in plain text from the client
		string ClientInput;
		cin >> ClientInput;
		// EX
		char Protocol = ClientInput[0];
		int Index = (int)ClientInput[1];
		string Detail = ClientInput.substr(2);

		// CURRENT PROTOCOL
		// c = card entering play
		// e = end of active players turn
		// a = attack 
		// f = effect that requires a trigger

		switch (Protocol) {
		case 'c':
		{
			Card *FromHand = PlayersInGame[Index]->Hand.at(stoi(Detail));

			Soul *SoulCard = nullptr;
			//Type2 *t2 = nullptr;
			//Type3 *t3 = nullptr;

			if (SoulCard = dynamic_cast<Soul*>(FromHand))
			{
				// Logically put the card in play
				PlayersInGame[Index]->SoulsInPlay.push_back(SoulCard);
				// Declare it has entered play
				cout << SoulCard->Name << " has entered the field for " << PlayersInGame[Index]->UserName << endl;
				// Remove the card from the hand if it succesfully enters the field
				PlayersInGame[Index]->Hand.erase(PlayersInGame[Index]->Hand.begin() + stoi(Detail));
				// Add the card to the stack
				Stack.push_back(SoulCard);
			}
			// if (t2 = dynamic_cast<Type2*>(p))
			//{
			//t2->type2Method();
			//}
			//else if (t3 = dynamic_cast<Type3*>(p))
			//{
			//t3->type3Method();
			//}
		}
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

