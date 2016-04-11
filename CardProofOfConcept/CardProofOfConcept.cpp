// CardProofOfConcept.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "Fire_Spirit.h"
#include "Pyromaniac.h"
#include <vector>
#include "Deck.h"

int main()
{
	//I want a factory...
	Fire_Spirit firespirit;
	Fire_Spirit firespirit2;
	Fire_Spirit firespirit3;
	Fire_Spirit firespirit4;
	Fire_Spirit firespirit5;

	Pyromaniac pyromaniac;

	cout << "Cost: " + to_string(firespirit.Cost) + '\n'
		<< "Name: " + firespirit.Name + '\n'
		<< "Description: " + firespirit.Description + '\n'
		<< "Attack: " + to_string(firespirit.Attack) + '\n'
		<< "Defense: " + to_string(firespirit.Defense) + '\n' << endl;

	cout << "Cost: " + to_string(pyromaniac.Cost) + '\n'
		 << "Name: " + pyromaniac.Name + '\n'
		 << "Description: " + pyromaniac.Description + '\n'
		 << "Attack: " + to_string(pyromaniac.Attack) + '\n'
		 << "Defense: " + to_string(pyromaniac.Defense) + '\n' << endl;

	//Some bizzare behaviour when adding a char to the end of a string
	//Im new to c++ okay
	cout << "Fire Spirit attacks Pyromaniac!\n" << endl;
	firespirit.Soul::Attacking(pyromaniac);

	cout << "Cost: " + to_string(pyromaniac.Cost) + '\n'
		<< "Name: " + pyromaniac.Name + '\n'
		<< "Description: " + pyromaniac.Description + '\n'
		<< "Attack: " + to_string(pyromaniac.Attack) + '\n'
		<< "Defense: " + to_string(pyromaniac.Defense) + '\n' << endl;

	Deck player1;
	player1.Add(firespirit);
	player1.Add(firespirit2);
	player1.Add(firespirit3);
	player1.Add(firespirit4);
	player1.Add(firespirit5);
	player1.Add(pyromaniac);

	//I don't work yet :)
	player1.Shuffle();

    return 0;
}

