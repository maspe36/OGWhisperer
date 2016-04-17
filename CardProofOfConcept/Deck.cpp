#include "stdafx.h" 
#include <string>
#include <memory>
#include "BaseClasses.h"

vector<Card*> Deck::Cards;

Deck::Deck()
{
}


Deck::~Deck()
{
}

auto Deck::Draw() -> Card*
{

	auto temp = Cards.front();

	Cards.erase(Cards.begin());

	return temp;
}

void Deck::Shuffle()
{

	vector<Card*> Copy(Cards);
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

void Deck::Add(Card* cardToAdd)
{
	Cards.push_back(cardToAdd);
}

void Deck::PrintDeck()
{
	for (auto i : Cards)
		cout << i->Name << endl;
}