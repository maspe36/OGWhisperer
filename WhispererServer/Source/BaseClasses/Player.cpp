#include "stdafx.h"
#include <string>
#include <algorithm>
#include <random>

#include "Player.h"
#include "Card.h"
#include "Soul.h"

Player::~Player()
{
}

Player::Player(vector<Card*> NewDeck, string NewUserName) : MainDeck(NewDeck), UserName(NewUserName)
{	
	// Set card owner
	for (size_t i = 0; i < MainDeck.size(); i++) 
	{
		MainDeck[i]->Owner = this;
	}

	ShuffleDeck();
}

string Player::HandToString()
{
	string CardsInHand;

	for (auto i : Hand) {
		CardsInHand += (i->ToString() + "#");
	}

	return CardsInHand;
}

string Player::ToString()
{
	//PlayerName+PlayerHealth
	return UserName + "+" + to_string(Health);
}

//Do I have a memory leak here? How can I free this memory?
string Player::SoulsInPlayToString()
{
	string SoulsInPlayString;

	for (auto i : SoulsInPlay) {
		SoulsInPlayString += (i->ToString() + "#");
	}

	return SoulsInPlayString;
}

bool Player::Compare(Player * OtherPlayer)
{
	// If username is not sufficent...
	// Must compare the following...
	// Health
	// Deck Contents
	// Username
	// Hand Contents
	// Souls on Field
	// Swifts on Field
	// Constants on Field
	// Graveyard

	// But for now we will assume that the username is sufficent enough
	if (UserName.compare(OtherPlayer->UserName) != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool Player::IsPlayable(int HandIndex)
{
	Card *ToPlay = Hand.at(HandIndex);
	// If this card exists in the players hand
	if (find(Hand.begin(), Hand.end(), ToPlay) != Hand.end()) {
		// Loop through devotion
		for (size_t i = 0; i < Devotion.size(); i++) {
			// At any point, does the player have insignifficant devotion?
			if (Devotion[i] < ToPlay->Cost[i]) {
				return false;
			}
		}
	}
	return true;
}

void Player::DrawCard()
{
	Card* temp = MainDeck.front();

	MainDeck.erase(MainDeck.begin());

	Hand.push_back(temp);
}

void Player::DrawCard(int Amount)
{
	for (int i = 0; i < Amount; i++) {
		Card* temp = MainDeck.front();

		MainDeck.erase(MainDeck.begin());

		Hand.push_back(temp);
	}
}

void Player::ShuffleDeck()
{
	std::shuffle(begin(MainDeck), end(MainDeck), seed);
}

void Player::HandToDeck()
{
	for (size_t i = 0; i < Hand.size(); i++) {
		Card* temp = Hand[i];

		MainDeck.push_back(temp);
	}
	Hand.clear();
}

void Player::PrintDeck() {
	// For debugging purposes, print the deck
	for (size_t i = 0; i < MainDeck.size(); i++) {
		cout << MainDeck[i]->Name << endl;
	}

	cout << endl;
	cout << " - - - - - - - - - - - - - " << endl;
	cout << endl;
}

