#include "stdafx.h"
#include "Deck.h"


Deck::Deck()
{
}


Deck::~Deck()
{
}

Card Deck::Draw()
{
	Card temp;
	temp = Cards.back();

	return temp;
}

void Deck::Shuffle()
{
	random_shuffle(Cards.begin(), Cards.end());
}

void Deck::Add(Card& cardToAdd)
{
	Cards.push_back(cardToAdd);
}

vector<Card> Deck::getCards()
{
	return Cards;
}
