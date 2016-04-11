#pragma once
#include<iostream>

using namespace std;

class Card
{
public:
	int Cost;
	string Name;
	string Description;

	Card() {}
	Card(int Cost, string Name, string Description) : Cost(Cost), Name(Name), Description(Description) {}
};

