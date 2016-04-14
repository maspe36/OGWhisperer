#pragma once
#include<vector>
#include "Card.h"
#include "stdafx.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand


class Deck
{
public:
	Deck();
	~Deck();
	auto Draw();
	void Shuffle();
	void Add(Card& cardToAdd);
	void PrintDeck();
	static vector<Card> Cards;
};

