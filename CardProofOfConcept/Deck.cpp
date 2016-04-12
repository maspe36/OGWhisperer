#include "stdafx.h"
#include "Deck.h"
#include<string>

vector<Card> Deck::Cards;

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

	vector<Card> Copy(Cards);
	int Max, Current;

	Max = Cards.size();

	Cards.clear();
	//Seed rand()
	srand(time(NULL));

	for (int Counter = 0; Counter < Max; Counter++)
	{
		Current = rand() % Copy.size();
		Cards.push_back(Copy[Current]);
		Copy.erase(Copy.begin() + Current);
	}
}

void Deck::Add(Card& cardToAdd)
{
	Cards.push_back(cardToAdd);
}

void Deck::PrintDeck()
{
	for (auto& i : Cards)
		cout << i.Name << endl;
}