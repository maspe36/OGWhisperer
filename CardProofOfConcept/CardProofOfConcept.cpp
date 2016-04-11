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
	Fire_Spirit firespirit1;
	Fire_Spirit firespirit2;
	Fire_Spirit firespirit3;
	Fire_Spirit firespirit4;
	Fire_Spirit firespirit5;

	Pyromaniac pyromaniac1;
	Pyromaniac pyromaniac2;
	Pyromaniac pyromaniac3;
	Pyromaniac pyromaniac4;
	Pyromaniac pyromaniac5;

	cout << "Cost: " + to_string(firespirit1.Cost) + '\n'
		<< "Name: " + firespirit1.Name + '\n'
		<< "Description: " + firespirit1.Description + '\n'
		<< "Attack: " + to_string(firespirit1.Attack) + '\n'
		<< "Defense: " + to_string(firespirit1.Defense) + '\n' << endl;

	cout << "Cost: " + to_string(pyromaniac1.Cost) + '\n'
		 << "Name: " + pyromaniac1.Name + '\n'
		 << "Description: " + pyromaniac1.Description + '\n'
		 << "Attack: " + to_string(pyromaniac1.Attack) + '\n'
		 << "Defense: " + to_string(pyromaniac1.Defense) + '\n' << endl;

	//Some bizzare behaviour when adding a char to the end of a string
	//Im new to c++ okay
	cout << "Fire Spirit attacks Pyromaniac!\n" << endl;
	firespirit1.Soul::Attacking(pyromaniac1);

	cout << "Cost: " + to_string(pyromaniac1.Cost) + '\n'
		<< "Name: " + pyromaniac1.Name + '\n'
		<< "Description: " + pyromaniac1.Description + '\n'
		<< "Attack: " + to_string(pyromaniac1.Attack) + '\n'
		<< "Defense: " + to_string(pyromaniac1.Defense) + '\n' << endl;

	Deck player1;
	player1.Add(firespirit1);
	player1.Add(firespirit2);
	player1.Add(firespirit3);
	player1.Add(firespirit4);
	player1.Add(firespirit5);

	player1.Add(pyromaniac1);
	player1.Add(pyromaniac2);
	player1.Add(pyromaniac3);
	player1.Add(pyromaniac4);
	player1.Add(pyromaniac5);

	cout << "Unshuffled Deck\n------------" << endl;
	player1.PrintDeck();

	player1.Shuffle();
	//random_shuffle(player1.Cards.begin(), player1.Cards.end());
	cout << "\nI just shuffled myself\n" << endl;

	cout << "Shuffled Deck\n------------" << endl;
	player1.PrintDeck();

    return 0;
}

