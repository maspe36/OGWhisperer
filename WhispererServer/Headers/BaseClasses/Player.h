#pragma once

#include "stdafx.h"
#include <vector>
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>
#include <random>
#include "GameState.h"

/* At some point there will
   probably need to be a unique
   hash in all objects for each game */

using namespace std;

class Card;
class Constant;
class Soul;
class Swift;
class GameState;

class Player
{
public:
	~Player();
	Player(string NewUserName, vector<Card*> NewDeck);

	int Health = 30;
	int MulligansTaken = 0;
	string UserName;
	bool KeepHand = false;

	mt19937 seed{ random_device{}() };

	vector<int> AvailableDevotion = { 1, 1, 1, 1, 1, 1 };
	vector<int> TotalDevotion = { 1, 1, 1, 1, 1, 1 };
	vector<Card*> MainDeck;
	vector<Card*> Hand;
	vector<Soul*> SoulsInPlay;
	vector<Swift*> SwiftsInPlay;
	vector<Constant*> ConstantsInPlay;
	vector<Card*> Graveyard;

	// With this all cards know what game they are in. 
	// This may cause some rewrites?
	GameState* CurrentGame;

	string HandToString();
	string GraveyardToString();
	string ToString();
	string SoulsInPlayToString();
	string ConstantsInPlayToString();

	bool IsDead = false;

	void DrawCard();
	void DrawCard(int Amount);
	void ShuffleDeck();
	void RefillDevotion();
	void HandToDeck();
	void PrintDeck();
};
