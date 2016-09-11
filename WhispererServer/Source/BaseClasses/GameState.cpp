#include "stdafx.h"
#include <string>
#include <sstream>
#include <algorithm>

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

	// Tell all players what game they are in
	for (auto i : Players)
	{
		i->CurrentGame = this;
	}
}

GameState::~GameState()
{
}

bool GameState::IsDeadMessage(Card* Target)
{
	if (Target->IsDead) {
		cout << Target->Owner->UserName << "'s " << Target->Name << " is dead!" << endl;
		Target->Owner->Graveyard.push_back(Target);
		Action* DeadAction = new Action({ Target }, Target->Owner, Action::_ActionType::Destroy);
		// What a chain...
		Target->Owner->CurrentGame->CheckEffects(DeadAction);
		delete DeadAction;
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
   removes it from the hand afterwards. Throws string.*/
void GameState::PlayCard(Card* Target)
{
	// Loop through devotion
	for (size_t i = 0; i < Target->Owner->AvailableDevotion.size(); i++)
	{
		// At any point, does the player have insignifficant devotion?
		if (Target->Owner->AvailableDevotion[i] < Target->Cost[i])
		{
			throw Target->Owner->UserName + " doesn't have enough devotion to play " + Target->Name + "!";
		}
	}
	if (Soul* SoulCard = dynamic_cast<Soul*>(Target))
	{
		// Logically put the card in play
		Target->Owner->SoulsInPlay.push_back(SoulCard);
		// Remove the card from the hand if it succesfully enters the field
		Target->Owner->Hand.erase(remove(Target->Owner->Hand.begin(), Target->Owner->Hand.end(), Target), Target->Owner->Hand.end());
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

	Action* CurrentAction = new Action({ Target }, Target->Owner, Action::_ActionType::Summon);
	CheckEffects(CurrentAction);
	delete CurrentAction;

	// Add the proper devotion
	// Note - If multi colored cards are ever introtuced this will need to be changed. Specifically the color parameter for Card.
	Target->Owner->TotalDevotion[Target->Color] = Target->Owner->TotalDevotion[Target->Color] + 1;
	// Now subtract from available devotion
	// Loop through all devotions and subtract it from the available devotion
	for (size_t i = 0; i < Target->Owner->TotalDevotion.size(); i++) {
		Target->Owner->AvailableDevotion[i] = Target->Owner->AvailableDevotion[i] - Target->Cost[i];
	}
}

void GameState::Start() {
	cout << "Begin Mulligans!" << endl;
	cout << endl;

	MulliganState();
	DrawTill5();

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

/* Draws cards for all players in the game until they have 5 cards in their hand */
void GameState::DrawTill5()
{
	for (auto i : PlayersInGame)
	{
		size_t HandSize = i->Hand.size();
		if (HandSize < 5)
		{
			i->DrawCard(5 - HandSize);
		}
	}
}

void GameState::TurnStartMaintenance()
{
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
	// Refill their devotion
	PlayersInGame[ActiveIndex]->RefillDevotion();
}

void GameState::PlayState()
{
	bool IsGameLive = true;

	// The first player needs to draw and have other misc things happen for their turn
	TurnStartMaintenance();

	// This is just to test obviously.
	//PlayersInGame[ActiveIndex]->AvailableDevotion = { 99,99,99,99,99,99 };
	//PlayersInGame[ActiveIndex]->TotalDevotion = { 99,99,99,99,99,99 };

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

		// CURRENT PROTOCOL
		// c = card entering play
		// e = end of active players turn
		// a = attack 

		switch (Protocol) {
		case GameState::CardProto:
		{
			int CardIndex = stoi(Parts[1]);

			try {
				PlayCard(PlayersInGame.at(ActiveIndex)->Hand.at(CardIndex));
			}
			catch (const string& s) {
				cout << s << endl;
			}
			catch (const out_of_range& e) {
				cout << "The card you are trying to play doesn't exist!" << endl;
			}
			catch (...) {
				cout << "Something went wrong when trying to play this card!" << endl;
			}
			break;
		}
		case GameState::AttackProto:
		{
			int AttackerIndex = stoi(Parts[1]);
			int TargetPlayerIndex = stoi(Parts[2]);
			string TargetType = Parts[3];

			// Attempt to attack
			try {
				// Are they attacking a soul?
				if (isdigit(TargetType[0]))
				{
					// Attack that players soul at TargetType
					PlayersInGame.at(ActiveIndex)->SoulsInPlay.at(AttackerIndex)->Attacking(PlayersInGame.at(TargetPlayerIndex)->SoulsInPlay.at(stoi(TargetType)));
				} // or a player?
				else {
					// Attack that players face at TargetType
					PlayersInGame.at(ActiveIndex)->SoulsInPlay.at(AttackerIndex)->Attacking(PlayersInGame.at(TargetPlayerIndex));
				}
			}// If they can't attack, what went wrong?
			catch (const string& s) {
				cout << s << endl;
			} // If they tried to attack something that doesn't exist
			catch (const out_of_range& e) {
				cout << "That target doesn't exist!" << endl;
			}
			catch (...) {
				cout << "Something went wrong during the attack!" << endl;
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
			TurnStartMaintenance();
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

		cout << "Clearing any dead cards..." << endl;
		// Check for dead cards
		ClearDeadCards();
		cout << "No more dead cards in play!" << endl;
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
			CardOrder[i]->Effect();
		}
	}
}

void GameState::ClearDeadCards()
{
	for (auto i : PlayersInGame)
	{
		// Remove all dead souls
		i->SoulsInPlay.erase(
			remove_if(i->SoulsInPlay.begin(), i->SoulsInPlay.end(), IsDeadMessage),
			i->SoulsInPlay.end()
		);
		// Remove all dead swifts 
		// Remove all dead constants
	}
	// Remove all dead cards in CardOrder
	CardOrder.erase(
		remove_if(CardOrder.begin(), CardOrder.end(), IsDead), \
		CardOrder.end()
	);
	for (auto p : PlayersInGame)
	{
		// check if there are any remaining dead souls (Effects can cause this to happen)
		for (auto s : p->SoulsInPlay)
		{
			if (s->IsDead)
			{
				// Recursive call to this method to keep removing dead cards. 
				// This will create the destroy action and checkeffects for us
				ClearDeadCards();
			}
		}
		// Do the same thing for swifts 
		// Do the same thing for constants
	}
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