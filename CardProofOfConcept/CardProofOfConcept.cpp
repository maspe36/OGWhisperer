// CardProofOfConcept.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include "BaseClasses.h"
#include "Cards.h"

int main()
{
	//I want a factory...
	Fire_Spirit firespirit1;
	Fire_Spirit firespirit2;

	Pyromaniac pyromaniac1;
	Pyromaniac pyromaniac2;

	Hellhound hellhound1;
	Hellhound hellhound2;

	Hellspark_Mutt hellsparkmutt1;
	Hellspark_Mutt hellsparkmutt2;

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

	player1.Add(pyromaniac1);
	player1.Add(pyromaniac2);

	player1.Add(hellhound1);
	player1.Add(hellhound2);

	player1.Add(hellsparkmutt1);
	player1.Add(hellsparkmutt2);

	cout << "Unshuffled Deck\n------------" << endl;
	player1.PrintDeck();

	player1.Shuffle();
	//random_shuffle(player1.Cards.begin(), player1.Cards.end());
	cout << "\nI just shuffled myself\n" << endl;

	cout << "Shuffled Deck\n------------" << endl;
	player1.PrintDeck();

	player1.Shuffle();
	//random_shuffle(player1.Cards.begin(), player1.Cards.end());
	cout << "\nI just shuffled myself\n" << endl;

	cout << "Shuffled Deck 2\n------------" << endl;
	player1.PrintDeck();

	cout << "\n" << endl;

	auto& temp = player1.Draw();
	cout << temp.Name << endl;

	cout << "After Draw Deck \n------------" << endl;
	player1.PrintDeck();

    return 0;
}

