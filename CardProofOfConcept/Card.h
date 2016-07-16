#pragma once
#include<iostream>
#include <vector>

using namespace std;

class Card
{
public:
	// Order of colors in cost vector (Alphabetical)
	// 0: Dark
	// 1: Earth
	// 2: Fire
	// 3: Light
	// 4: Water
	// 5: Wind
	vector<int> Cost;
	// Name of the card
	string Name;
	// The description or flavour text of a card
	string Description;
	// The effect of a card in text
	string EffectText;
	// The color of a card
	string Color;

	virtual ~Card();
	string ToString();
	Card(vector<int> Cost, string Name, string EffectText, string Description, string Color) : 
		Cost(Cost), Name(Name), EffectText(EffectText), Description(Description), Color(Color) {}
};

