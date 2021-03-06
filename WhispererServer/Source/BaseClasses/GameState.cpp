#include "stdafx.h"
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/algorithm/string.hpp>

#include "Constant.h"
#include "Creature.h"
#include "Spell.h"
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

bool GameState::IsConstantDeadMessage(Card* Target)
{
	if (Target->IsDead) {
		cout << Target->Owner->UserName << "'s " << Target->Name << " is dead!" << endl;
		Target->Owner->Graveyard.push_back(Target);
		Action* DeadAction = new Action({ Target }, Target->Owner, Action::_ActionType::Destroy);
		// What a chain...
		Target->Owner->CurrentGame->CheckEffects(DeadAction);
		delete DeadAction;
		// Only constants part.
		Constant* ConstantCard = dynamic_cast<Constant*>(Target);
		ConstantCard->IsDeadMaintenance();
		return true;
	}
	return false;
}

/* If a card is dead, send it to the graveyard, check effects, and print a message!
This is used for clear dead cards. */
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

/* If a card is dead return true. */
bool GameState::IsDead(Card* Target)
{
	if (Target->IsDead) {
		return true;
	}
	return false;
}

/* If a player is dead return true. */
bool GameState::IsPlayerDead(Player * Target)
{
	if (Target->IsDead)
	{
		return true;
	}
	return false;
}

/* Iterates through the players in the game and sets the active index
to the index of the current players turn. If we hit the end of players,
we start over at the 0 index player turn.*/
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
	// Add the card to the stack
	CardOrder.push_back(Target);

	Action* CurrentAction = new Action({ Target }, Target->Owner, Action::_ActionType::Summon);
	CheckEffects(CurrentAction);
	delete CurrentAction;

	// Loop through devotion
	for (size_t i = 0; i < Target->Owner->AvailableDevotion.size(); i++)
	{
		// At any point, does the player have insignifficant devotion?
		if (Target->Owner->AvailableDevotion.at(i) < Target->Cost.at(i))
		{
			throw Target->Owner->UserName + " doesn't have enough devotion to play " + Target->Name + "!";
		}
	}
	if (Creature* CreatureCard = dynamic_cast<Creature*>(Target))
	{
		// Logically put the card in play
		Target->Owner->CreaturesInPlay.push_back(CreatureCard);
	}
	if (Spell* SpellCard = dynamic_cast<Spell*>(Target))
	{
		// Logically put the card in play
		Target->Owner->SpellsInPlay.push_back(SpellCard);
	}
	if (Constant* ConstantCard = dynamic_cast<Constant*>(Target))
	{
		// Logically put the card in play
		Target->Owner->ConstantsInPlay.push_back(ConstantCard);
	}

	// Remove the card from the hand if it succesfully enters the field
	Target->Owner->Hand.erase(remove(Target->Owner->Hand.begin(), Target->Owner->Hand.end(), Target), Target->Owner->Hand.end());

	// Add the proper devotion
	// Note - If multi colored cards are ever introtuced this will need to be changed. Specifically the color parameter for Card.
	Target->Owner->TotalDevotion.at(Target->Color) = Target->Owner->TotalDevotion.at(Target->Color) + 1;
	// Now subtract from available devotion
	// Loop through all devotions and subtract it from the available devotion
	for (size_t i = 0; i < Target->Owner->TotalDevotion.size(); i++) {
		Target->Owner->AvailableDevotion.at(i) = Target->Owner->AvailableDevotion.at(i) - Target->Cost.at(i);
	}

	cout << Target->Name << " has entered the field for " << Target->Owner->UserName << "!" << endl;
}

/* Starts the game! */
void GameState::Start() {
	cout << "Begin Mulligans!" << endl;
	cout << endl;

	MulliganState();
	DrawTill5();

	cout << "End Mulligans..." << endl;
	cout << endl;
	cout << "Start Game!" << endl;

	PlayState();

	cout << "End game..." << endl;
	EndGameState();
	cout << "Jobs done." << endl;
}

/* Pusedo-Asynchronous function. While there is a player that hasn't decalred they are keeping
we listen for a decision. The numbers we are listening for are player index and keep or not.
Eventually this needs to make sure we are getting a message back from the correct player
so another player can't maliciously mulligan for another player. */
void GameState::MulliganState()
{
	bool IsMulliganState = true;
	size_t MaxPlayerKeeps = PlayersInGame.size();
	int PlayersThatKept = 0;

	for (auto i : PlayersInGame) {
		// Draw 5 cards before the game starts
		i->DrawCard(5);
	}

	while (IsMulliganState) {
		cout << "Max Player Keeps: " << MaxPlayerKeeps << endl;
		cout << "Players Keeping: " << PlayersThatKept << endl;
		cout << endl;

		// Show them the cards
		for (size_t i = 0; i < PlayersInGame.size(); i++) {
			cout << PlayersInGame.at(i)->UserName << endl;
			cout << "----------" << endl;
			cout << PlayersInGame.at(i)->HandToString() << endl;
			cout << "----------------------------------------" << endl;
			cout << endl;
		}

		// Get the user input
		// UserIndex	:	IsMulligan
		// Parts[0]		:	Parts[1]
		string Choice;
		vector<string> Parts;

		try
		{
			getline(cin, Choice);
			boost::split(Parts, Choice, boost::is_any_of(":"));

			// Grab the first (only..) char.
			int Index = stoi(Parts.at(0));
			int IsMulligan = stoi(Parts.at(1));

			// They want to mulligan
			if (IsMulligan == 1) {
				// If they haven't mulliganed 5+ times...
				if (!(PlayersInGame.at(Index)->MulligansTaken >= 5)) {
					// Increase the mulligan counter
					PlayersInGame.at(Index)->MulligansTaken = (PlayersInGame.at(Index)->MulligansTaken + 1);
					// Return their hand to the deck
					PlayersInGame.at(Index)->HandToDeck();
					// Shuffle the deck!
					PlayersInGame.at(Index)->ShuffleDeck();
					// Draw 5 cards minus the amount of mulligans taken!
					PlayersInGame.at(Index)->DrawCard(5 - PlayersInGame.at(Index)->MulligansTaken);
					// Have they mulliganed too many times?
					if (PlayersInGame.at(Index)->MulligansTaken >= 5) {
						PlayersThatKept++;
						PlayersInGame.at(Index)->KeepHand = true;
					}
				}
			}
			// They want to keep
			else {
				PlayersInGame.at(Index)->KeepHand = true;
				PlayersThatKept++;
			}
			// If every player has decided to keep, we are done mulliganning
			if (PlayersThatKept == MaxPlayerKeeps) {
				IsMulliganState = false;
			}
		}
		catch (const out_of_range& e) {
			cout << "The player or mulligan choice doesn't exist! Check your input and try again!" << endl;
		}
		catch (...)
		{
			cout << "Something went wrong! Please check your input and try again!" << endl;
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
	Action* TurnStartAction = new Action(PlayersInGame.at(ActiveIndex), Action::_ActionType::TurnStart);
	CheckEffects(TurnStartAction);
	delete TurnStartAction;

	//The now active player needs to draw and have their mana refilled
	PlayersInGame.at(ActiveIndex)->DrawCard();
	// Check if there are any effects from drawing a card
	// Pass in the card drawn
	Action* DrawAction = new Action({ PlayersInGame.at(ActiveIndex)->Hand.back() }, PlayersInGame.at(ActiveIndex), Action::_ActionType::Draw);
	CheckEffects(DrawAction);
	delete DrawAction;

	for (auto i : PlayersInGame.at(ActiveIndex)->CreaturesInPlay)
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
	PlayersInGame.at(ActiveIndex)->RefillDevotion();
}

void GameState::PlayState()
{
	bool IsGameLive = true;

	// The first player needs to draw and have other misc things happen for their turn
	TurnStartMaintenance();

	// This is just to test obviously.
	for (auto p : PlayersInGame) {
		p->AvailableDevotion = { 99,99,99,99,99,99 };
		p->TotalDevotion = { 99,99,99,99,99,99 };
	}
	
	//While the game is ongoing or 'live'
	while (IsGameLive)
	{
		cout << "----------" << PlayersInGame.at(ActiveIndex)->UserName << "----------" << endl;
		cout << "Hand: " << PlayersInGame.at(ActiveIndex)->HandToString() << endl;
		cout << "Graveyard: " << PlayersInGame.at(ActiveIndex)->GraveyardToString() << endl;
		cout << "Health: " << PlayersInGame.at(ActiveIndex)->Health << endl;
		cout << "----------Devotion----------" << endl;
		cout << "Dark: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(0) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(0) << endl;
		cout << "Earth: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(1) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(1) << endl;
		cout << "Fire: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(2) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(2) << endl;
		cout << "Light: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(3) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(3) << endl;
		cout << "Water: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(4) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(4) << endl;
		cout << "Wind: " << PlayersInGame.at(ActiveIndex)->AvailableDevotion.at(5) << "/" << PlayersInGame.at(ActiveIndex)->TotalDevotion.at(5) << endl;
		cout << "----------In Play----------" << endl;
		cout << "Creatures in play: " << PlayersInGame.at(ActiveIndex)->CreaturesInPlayToString() << endl;
		cout << "Constants in play: " << PlayersInGame.at(ActiveIndex)->ConstantsInPlayToString() << endl;

		// Should be a message recieved in plain text from the client
		string ClientInput;
		vector<string> Parts;
		char Protocol;

		try
		{
			getline(cin, ClientInput);
			boost::split(Parts, ClientInput, boost::is_any_of(delemiter));
			Protocol = ClientInput.at(0);
		}
		catch (...)
		{
			cout << "ERROR: Please check your message!" << endl;
		}

		// CURRENT PROTOCOL
		// c = card entering play
		// e = end of active players turn
		// a = attack 

		switch (Protocol) {
		case GameState::CardProto:
		{
			try
			{
				int CardIndex = stoi(Parts.at(1));
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
			// Attempt to attack
			try
			{
				int AttackerIndex = stoi(Parts.at(1));
				int TargetPlayerIndex = stoi(Parts.at(2));
				string TargetType = Parts.at(3);
				// Are they attacking a creature?
				if (isdigit(TargetType.at(0)))
				{
					// Attack that players creature at TargetType
					PlayersInGame.at(ActiveIndex)->CreaturesInPlay.at(AttackerIndex)->Attacking(PlayersInGame.at(TargetPlayerIndex)->CreaturesInPlay.at(stoi(TargetType)));
				} // or a player?
				else {
					// Attack that players face at TargetType
					PlayersInGame.at(ActiveIndex)->CreaturesInPlay.at(AttackerIndex)->Attacking(PlayersInGame.at(TargetPlayerIndex));
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
			Action* TurnEndAction = new Action(PlayersInGame.at(ActiveIndex), Action::_ActionType::TurnEnd);
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
}

void GameState::EndGameState()
{
	cout << PlayersInGame.at(0)->UserName << " has won!" << endl;
	cout << "Congratulations!" << endl;
	cout << "-------------------------" << endl;
	cout << "Game Over!" << endl;
}

/* Loops through all cards in play and checks if their effect is triggered by passing in a
current action to IsEffecttriggered. If it is triggered we go ahead and call the effect function
of the card.*/
void GameState::CheckEffects(Action* CurrentAction)
{
	for (size_t i = 0; i < CardOrder.size(); i++)
	{
		if (CardOrder.at(i)->IsEffectTriggered(CurrentAction)) {
			CardOrder.at(i)->Effect();
		}
	}
}

/* Loops through all players in the game and removes all cards from the field.
It is possible for cards to still be alive after this (Downfall effects, etc) so
at the end of this method we recheck if there is anything dead, and if there is
we recursively call this method. Be careful! */
void GameState::ClearDeadCards()
{
	for (auto i : PlayersInGame)
	{
		// Remove all dead creatures
		i->CreaturesInPlay.erase(
			remove_if(i->CreaturesInPlay.begin(), i->CreaturesInPlay.end(), IsDeadMessage),
			i->CreaturesInPlay.end()
		);
		i->SpellsInPlay.erase(
			remove_if(i->SpellsInPlay.begin(), i->SpellsInPlay.end(), IsDeadMessage),
			i->SpellsInPlay.end()
		);
		i->ConstantsInPlay.erase(
			remove_if(i->ConstantsInPlay.begin(), i->ConstantsInPlay.end(), IsConstantDeadMessage),
			i->ConstantsInPlay.end()
		);
	}
	// Remove all dead cards in CardOrder
	CardOrder.erase(
		remove_if(CardOrder.begin(), CardOrder.end(), IsDead),
		CardOrder.end()
	);
	for (auto p : PlayersInGame)
	{
		// check if there are any remaining dead creatures (Effects can cause this to happen)
		for (auto s : p->CreaturesInPlay)
		{
			if (s->IsDead)
			{
				// Recursive call to this method to keep removing dead cards. 
				// This will create the destroy action and checkeffects for us
				ClearDeadCards();
			}
		}
		// check if there are any remaining dead constants (Effects can cause this to happen)
		for (auto c : p->ConstantsInPlay)
		{
			if (c->IsDead)
			{
				// Recursive call to this method to keep removing dead cards. 
				// This will create the destroy action and checkeffects for us
				ClearDeadCards();
			}
		}
	}
}

/* Loops through all players in the game and checks if they are dead.
If they are we remove them from the game. */
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

/* Checks if there is only 1 player left in the game, if yes we break the game loop. */
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