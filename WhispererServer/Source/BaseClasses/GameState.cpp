#include "stdafx.h"
#include <string>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "Soul.h"
#include "Player.h"
#include "GameState.h"
#include "Action.h"

GameState::GameState(vector<Player*> Players) : PlayersInGame(Players)
{
	// Initialize ActivePlayer
	// This determines who goes first, we need to make it random whoever goes first
	// For now we can just let the first player in the vector go first
	ActiveIndex = 0;
}

GameState::~GameState()
{
}

void GameState::ChangeActivePlayer() {
	//If the active player is the last item in the vector
	if (ActiveIndex == (PlayersInGame.size() - 1)) {
		//Set it to the front of the vector
		ActiveIndex = 0;
	}
	else {
		ActiveIndex++;
	}
}

/* Play card from given owners hand at the given index.
   Puts the card into the correct area of play and
   removes it from the hand afterwards */
void GameState::PlayCard(int PlayerIndex, int HandIndex)
{
	Card *FromHand = PlayersInGame[PlayerIndex]->Hand.at(HandIndex);

	if (Soul* SoulCard = dynamic_cast<Soul*>(FromHand))
	{
		// Logically put the card in play
		PlayersInGame[PlayerIndex]->SoulsInPlay.push_back(SoulCard);
		// Remove the card from the hand if it succesfully enters the field
		PlayersInGame[PlayerIndex]->Hand.erase(PlayersInGame[PlayerIndex]->Hand.begin() + HandIndex);
		// Add the card to the stack
		CardOrder.push_back(SoulCard);
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
	cout << "Begin Mulligans!" << endl;
	cout << endl;

	MulliganState();

	cout << "End Mulligans..." << endl;
	cout << endl;
	cout << "Start Game!" << endl;

	PlayState();

}

void GameState::MulliganState()
{
	bool IsMulliganState = true;
	size_t MaxPlayerKeeps = PlayersInGame.size();
	int PlayersThatKept = 0;

	for (size_t i = 0; i < PlayersInGame.size(); i++) {
		// Draw 5 cards before the game starts
		PlayersInGame[i]->DrawCard(5);
	}

	while (IsMulliganState) {
		cout << "Max Player Keeps: " << MaxPlayerKeeps << endl;
		cout << "Players Keeping: " << PlayersThatKept << endl;
		cout << endl;

		// Show them the cards
		for (size_t i = 0; i < PlayersInGame.size(); i++) {
			cout << PlayersInGame[i]->UserName << endl;
			cout << PlayersInGame[i]->HandToString() << endl;
		}

		// Get the user input
		// UserIndex	:	IsMulligan
		// Parts[0]		:	Parts[1]
		string Choice;
		getline(cin, Choice);

		vector<string> Parts;

		boost::split(Parts, Choice, boost::is_any_of(":"));

		// Grab the first (only..) char.
		int Index = stoi(Parts[0]);
		int IsMulligan = stoi(Parts[1]);

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
				// Shuffle the deck!
				PlayersInGame[Index]->ShuffleDeck();
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
}

void GameState::PlayState()
{
	bool IsGameLive = true;

	PlayersInGame[ActiveIndex]->Devotion[2] = 10;

	//While the game is ongoing or 'live'
	while (IsGameLive)
	{
		cout << "----------" << PlayersInGame[ActiveIndex]->UserName << "----------" << endl;
		cout << "Hand: " << PlayersInGame[ActiveIndex]->HandToString() << endl;
		cout << "Health: " << PlayersInGame[ActiveIndex]->Health << endl;
		cout << "----------Devotion----------" << endl;
		cout << "Dark: " << PlayersInGame[ActiveIndex]->Devotion[0] << endl;
		cout << "Earth: " << PlayersInGame[ActiveIndex]->Devotion[1] << endl;
		cout << "Fire: " << PlayersInGame[ActiveIndex]->Devotion[2] << endl;
		cout << "Light: " << PlayersInGame[ActiveIndex]->Devotion[3] << endl;
		cout << "Water: " << PlayersInGame[ActiveIndex]->Devotion[4] << endl;
		cout << "Wind: " << PlayersInGame[ActiveIndex]->Devotion[5] << endl;
		cout << "----------In Play----------" << endl;
		cout << "Souls in play: " << PlayersInGame[ActiveIndex]->SoulsInPlayToString() << endl;

		// Should be a message recieved in plain text from the client
		string ClientInput;
		getline(cin, ClientInput);

		vector<string> Parts;

		boost::split(Parts, ClientInput, boost::is_any_of(delemiter));

		// Grab the frist char from the string (only char)
		char Protocol = ClientInput[0];

		Action* CurrentAction = new Action;

		// CURRENT PROTOCOL
		// c = card entering play
		// e = end of active players turn
		// a = attack 

		switch (Protocol) {
		case GameState::CardProto:
		{
			int Index = stoi(Parts[1]);
			int CardIndex = stoi(Parts[2]);
			// Maybe surround this in a try catch so we can give the user 
			// detailed explanations on why they cannot do what they want to do
			Card *FromHand = PlayersInGame[Index]->Hand.at(CardIndex);
			cout << "Checking if " << FromHand->Name << " can be played..." << endl;
			// If this player has enough mana and the card exists in their hand
			if (PlayersInGame[Index]->IsPlayable(CardIndex)) {
				cout << FromHand->Name << " is playable!" << endl;
				// Go ahead and play it. This method removes it from the hand as well.
				PlayCard(Index, CardIndex);
				// Declare it has entered play
				cout << FromHand->Name << " has entered the field for " << PlayersInGame[Index]->UserName << endl;
				// Fill Current Action Accordingly
				CurrentAction->ActionType = Action::_ActionType::Summon;
				CurrentAction->CardTargets.push_back(FromHand);
				CurrentAction->Owner = PlayersInGame[Index];
			}
			break;
		}
		case GameState::EndTurnProto:
		{
			//int Index = stoi(Parts[1]);
			//Active player changes from the active player that entered the switch here
			ChangeActivePlayer();
			//The now active player needs to draw and have their mana refilled
			break;
		}
		} // end of switch. This is annoying
		cout << "end of switch" << endl;
		cout << "Checking effects..." << endl;

		// Check effects
		CheckEffects(CurrentAction);

		cout << "All effects checked!" << endl;
		cout << "Deleteing CurrentAction..." << endl;
		// We don't need it anymore
		delete CurrentAction;
		cout << "CurrentAction deleted!" << endl;
	}
}

void GameState::CheckEffects(Action* CurrentAction)
{
	for (size_t i = 0; i < CardOrder.size(); i++)
	{
		if (CardOrder[i]->IsEffectTriggered(CurrentAction)) {
			CardOrder[i]->Effect(this);
		}
	}
}

