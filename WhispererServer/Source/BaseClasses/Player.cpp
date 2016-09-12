#include "stdafx.h"
#include <string>
#include <algorithm>
#include <random>

#include "Player.h"
#include "Card.h"
#include "Soul.h"
#include "Affect.h"

Player::~Player()
{
}

Player::Player(string NewUserName, vector<Card*> NewDeck) : UserName(NewUserName), MainDeck(NewDeck)
{	
	// Set card owner
	for (size_t i = 0; i < MainDeck.size(); i++) 
	{
		MainDeck[i]->Owner = this;
	}

	ShuffleDeck();
}

/* Returns a string with names of all cards in hand. Name#Name#Name */
string Player::HandToString()
{
	stringstream CardsInHand;

	for (auto i : Hand) {
		CardsInHand << i->Name << "; ";
	}

	return CardsInHand.str();
}

/* Returns a list of all cards names in a players graveyard.
Name#Name#Name*/
string Player::GraveyardToString()
{
	string GraveyardCards;

	for (auto i : Graveyard) {
		GraveyardCards += (i->Name + "#");
	}

	return GraveyardCards;
}

/* Returns the username and health of a player. Name+Health */
string Player::ToString()
{
	//PlayerName+PlayerHealth
	return UserName + "+" + to_string(Health);
}

/* Returns a formatted JSON of all the souls in play for this player.
Cannot be returned alone, it is missing a wrapping {} on purpose.*/
string Player::SoulsInPlayToString()
{
	ostringstream SoulsInPlayString;

	for (auto i : SoulsInPlay) {
		SoulsInPlayString << (i->ToString()) << "; ";
	}

	return SoulsInPlayString.str();
}

/* Draws a single card from the front a deck (vetor<Card*>) */
void Player::DrawCard()
{
	Card* temp = MainDeck.front();

	MainDeck.erase(MainDeck.begin());

	Hand.push_back(temp);
}

/* Draw the specified amount of cards from the deck (vector<Card*>) */
void Player::DrawCard(int Amount)
{
	for (int i = 0; i < Amount; i++) {
		Card* temp = MainDeck.front();

		MainDeck.erase(MainDeck.begin());

		Hand.push_back(temp);
	}
}

/* Shuffles a players deck using std::shuffle. */
void Player::ShuffleDeck()
{
	shuffle(begin(MainDeck), end(MainDeck), seed);
}

/* Refills a players AvailableDevotion to their TotalDevotion. */
void Player::RefillDevotion()
{
	for (size_t i = 0; i < TotalDevotion.size(); i++) {
		AvailableDevotion[i] = TotalDevotion[i];
	}
}

/* Returns every card in a players hand to their deck. Clears their hand. */
void Player::HandToDeck()
{
	for (size_t i = 0; i < Hand.size(); i++) {
		Card* temp = Hand[i];

		MainDeck.push_back(temp);
	}
	Hand.clear();
}

/* Prints all the cards in a players deck. */
void Player::PrintDeck() {
	// For debugging purposes, print the deck
	for (size_t i = 0; i < MainDeck.size(); i++) {
		cout << MainDeck[i]->Name << endl;
	}

	cout << endl;
	cout << " - - - - - - - - - - - - - " << endl;
	cout << endl;
}

