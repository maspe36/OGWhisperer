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

bool GameState::IsDeadMessage(Card* Target)
{
	if (Target->IsDead) {
		cout << Target->Owner->UserName << "'s " << Target->Name << " is dead!" << endl;
		Target->Owner->Graveyard.push_back(Target);
		return true;
	}
	return false;
}

bool GameState::IsDead(Card* Target)
{
	if (Target->IsDead) {
		return true;
	}
	return false;
}

bool GameState::IsPlayerDead(Player * Target)
{
	if (Target->IsDead) 
	{
		return true;
	}
	return false;
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

	// Add the proper devotion
	// Note - If multi colored cards are ever introtuced this will need to be changed. Specifically the color parameter for Card.
	PlayersInGame[PlayerIndex]->TotalDevotion[FromHand->Color] = PlayersInGame[PlayerIndex]->TotalDevotion[FromHand->Color] + 1;
	// Now subtract from available devotion
	// Loop through all devotions and subtract it from the available devotion
	for (size_t i = 0; i < PlayersInGame[PlayerIndex]->TotalDevotion.size(); i++) {
		PlayersInGame[PlayerIndex]->AvailableDevotion[i] = PlayersInGame[PlayerIndex]->AvailableDevotion[i] - FromHand->Cost[i];
	}
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

	//While the game is ongoing or 'live'
	while (IsGameLive)
	{
		cout << "----------" << PlayersInGame[ActiveIndex]->UserName << "----------" << endl;
		cout << "Hand: " << PlayersInGame[ActiveIndex]->HandToString() << endl;
		cout << "Graveyard: " << PlayersInGame[ActiveIndex]->GraveyardToString() << endl;
		cout << "Health: " << PlayersInGame[ActiveIndex]->Health << endl;
		cout << "----------Devotion----------" << endl;
		cout << "Dark: " << PlayersInGame[ActiveIndex]->AvailableDevotion[0] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[0] << endl;
		cout << "Earth: " << PlayersInGame[ActiveIndex]->AvailableDevotion[1] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[1] << endl;
		cout << "Fire: " << PlayersInGame[ActiveIndex]->AvailableDevotion[2] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[2] << endl;
		cout << "Light: " << PlayersInGame[ActiveIndex]->AvailableDevotion[3] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[3] << endl;
		cout << "Water: " << PlayersInGame[ActiveIndex]->AvailableDevotion[4] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[4] << endl;
		cout << "Wind: " << PlayersInGame[ActiveIndex]->AvailableDevotion[5] << "/" << PlayersInGame[ActiveIndex]->TotalDevotion[5] << endl;
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
			int CardIndex = stoi(Parts[1]);
			// Maybe surround this in a try catch so we can give the user 
			// detailed explanations on why they cannot do what they want to do
			Card *FromHand = PlayersInGame[ActiveIndex]->Hand.at(CardIndex);
			cout << "Checking if " << FromHand->Name << " can be played..." << endl;
			// If this player has enough mana and the card exists in their hand
			if (PlayersInGame[ActiveIndex]->IsPlayable(CardIndex)) {
				cout << FromHand->Name << " is playable!" << endl;
				// Go ahead and play it. This method removes it from the hand as well.
				PlayCard(ActiveIndex, CardIndex);
				// Declare it has entered play
				cout << FromHand->Name << " has entered the field for " << PlayersInGame[ActiveIndex]->UserName << endl;
				// Fill Current Action Accordingly
				CurrentAction->ActionType = Action::_ActionType::Summon;
				CurrentAction->CardTargets.push_back(FromHand);
				CurrentAction->Owner = PlayersInGame[ActiveIndex];
			}
			break;
		}
		case GameState::AttackProto:
		{
			int AttackerIndex = stoi(Parts[1]);
			int TargetPlayerIndex = stoi(Parts[2]);
			string TargetType = Parts[3];
			// Can they even attack?
			if (PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->CanAttack) 
			{
				// Make sure to reduce flurry (number of times a soul can attack in a turn)
				PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->_Flurry = 
					PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->_Flurry - 1;

				if (PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->_Flurry <= 0)
				{
					PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->CanAttack = false;
				}
				// If they are attacking a soul...
				if (isdigit(TargetType[0]))
				{
					// Convert the string to the appropriate int
					int DeffenderIndex = stoi(TargetType);

					// Attack!
					PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Attacking(PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex]);

					// Set the CurrentAction object
					CurrentAction->Attacker = PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex];
					CurrentAction->Target = PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex];
					CurrentAction->Owner = PlayersInGame[ActiveIndex];
					CurrentAction->ActionType = Action::_ActionType::Attack;

					cout << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Owner->UserName << "'s " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Name << " attacked " << PlayersInGame[TargetPlayerIndex]->SoulsInPlay[AttackerIndex]->Owner->UserName << "'s " << PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex]->Name
						<< " for " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->CurrentAttack << "!" << endl;
					cout << PlayersInGame[TargetPlayerIndex]->SoulsInPlay[AttackerIndex]->Owner->UserName << "'s " << PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex]->Name
						<< " has " << PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex]->CurrentDefense << " health!" << endl;
					cout << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Owner->UserName << "'s " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Name << " was hit for "
						<< PlayersInGame[TargetPlayerIndex]->SoulsInPlay[DeffenderIndex]->CurrentAttack << "!" << endl;
					cout << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Owner->UserName << "'s " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Name << " has " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->CurrentDefense << " health!" << endl;
				}
				else // They are attacking a player... 
				{
					// Attack!
					PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Attacking(PlayersInGame[TargetPlayerIndex]);

					// Set CurrentAction object
					CurrentAction->Attacker = PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex];
					CurrentAction->PlayerTarget = PlayersInGame[TargetPlayerIndex];
					CurrentAction->Owner = PlayersInGame[ActiveIndex];
					CurrentAction->ActionType = Action::_ActionType::Attack;

					cout << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Name << " attacked " << PlayersInGame[TargetPlayerIndex]->UserName
						<< " for " << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->CurrentAttack << "!" << endl;
					cout << PlayersInGame[TargetPlayerIndex]->UserName << " has " << PlayersInGame[TargetPlayerIndex]->Health << " health!" << endl;
				}
			}
			else 
			{
				cout << PlayersInGame[ActiveIndex]->SoulsInPlay[AttackerIndex]->Name << " cannot attack!" << endl;
			}
			break;
		}
		case GameState::EndTurnProto:
		{
			// Check if anything is going on at the end of the turn
			Action* TurnEndAction = new Action(PlayersInGame[ActiveIndex], Action::_ActionType::TurnEnd);
			CheckEffects(TurnEndAction);
			delete TurnEndAction;

			// Active player changes from the active player that entered the switch here
			ChangeActivePlayer();
		
			// At the start of a players turn...
			// Remove the statis from all souls by one unless it is zero
			for (auto i : PlayersInGame[ActiveIndex]->SoulsInPlay)
			{
				if (i->_Statis > 0)
				{
					i->_Statis = 
						i->_Statis - 1;
				}
				// If it is zero they can attack
				if (i->_Statis == 0)
				{
					i->CanAttack = true;
				}
				// Reset the number of attacks a card can have
				i->_Flurry = i->_OriginalFlurry;
			}

			// The active index now reflects the next players turn
			// Check if there are any beginning of turn effects
			Action* TurnStartAction = new Action(PlayersInGame[ActiveIndex], Action::_ActionType::TurnStart);
			CheckEffects(TurnStartAction);
			delete TurnStartAction;

			//The now active player needs to draw and have their mana refilled
			PlayersInGame[ActiveIndex]->DrawCard();
			// Check if there are any effects from drawing a card
			// Pass in the card drawn
			Action* DrawAction = new Action({ PlayersInGame[ActiveIndex]->Hand.back() }, PlayersInGame[ActiveIndex], Action::_ActionType::Draw);
			CheckEffects(DrawAction);
			delete DrawAction;

			PlayersInGame[ActiveIndex]->RefillDevotion();
			// God, we can finally say that the player may now input commands.
			break;
		}
		} // end of switch. This is annoying
		cout << "Clearing any dead players..." << endl;
		// Check for losers
		ClearDeadPlayers();
		cout << "No more dead players in game!" << endl;
		
		cout << "Checking for winners..." << endl;
		// Is the game over?
		if (IsGameOver()) 
		{
			IsGameLive = false;
		}
		cout << "Done checking winners!" << endl;

		cout << "Checking effects..." << endl;
		// Check effects
		CheckEffects(CurrentAction);
		cout << "All effects checked!" << endl;

		cout << "Clearing any dead cards..." << endl;
		// Check for dead cards
		ClearDeadCards();
		cout << "No more dead cards in play!" << endl;

		cout << "Deleteing CurrentAction..." << endl;
		// We don't need it anymore
		delete CurrentAction;
		cout << "CurrentAction deleted!" << endl;
	}
	cout << PlayersInGame[0]->UserName << " has won!" << endl;
	cout << "Congratulations!" << endl;
	cout << "-------------------------" << endl;
	cout << "Game Over!" << endl;
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

void GameState::ClearDeadCards()
{
	for (auto i : PlayersInGame)
	{
		// Remove all dead souls
		i->SoulsInPlay.erase(
			remove_if(i->SoulsInPlay.begin(), i->SoulsInPlay.end(),IsDeadMessage), 
			i->SoulsInPlay.end()
		);
		// Remove all dead swifts 
		// Remove all dead consts
	}
	// Remove all dead cards in CardOrder
	CardOrder.erase(
		remove_if(CardOrder.begin(), CardOrder.end(),IsDead), \
		CardOrder.end()
	);
}

void GameState::ClearDeadPlayers() 
{
	for (auto i : PlayersInGame) 
	{
		if (i->IsDead) {
			cout << i->UserName << " has lost!" << endl;
		}
	}
	PlayersInGame.erase(
		remove_if(PlayersInGame.begin(), PlayersInGame.end(), IsPlayerDead),
		PlayersInGame.end()
	);
}

bool GameState::IsGameOver() 
{
	if (PlayersInGame.size() == 1) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}