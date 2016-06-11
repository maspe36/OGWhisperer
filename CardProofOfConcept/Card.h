#pragma once
#include<iostream>

using namespace std;

class Card
{
public:
	int Cost;
	string Name;
	string Description;
	string EffectText;

	virtual ~Card();
	string ToString();
	Card(int Cost, string Name, string EffectText, string Description) : Cost(Cost), Name(Name), EffectText(EffectText), Description(Description) {}
};

