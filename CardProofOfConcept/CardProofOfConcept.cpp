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
	Fire_Spirit *firespirit1 = new Fire_Spirit();
	Fire_Spirit *firespirit2 = new Fire_Spirit();

	Pyromaniac *pyromaniac1 = new Pyromaniac();
	Pyromaniac *pyromaniac2 = new Pyromaniac();

	Hellhound *hellhound1 = new Hellhound();
	Hellhound *hellhound2 = new Hellhound();

	Hellspark_Mutt *hellsparkmutt1 = new Hellspark_Mutt();
	Hellspark_Mutt *hellsparkmutt2 = new Hellspark_Mutt();

	cout << "Cost: " + to_string(firespirit1->Cost) + '\n'
		<< "Name: " + firespirit1->Name + '\n'
		<< "Description: " + firespirit1->Description + '\n'
		<< "Attack: " + to_string(firespirit1->Attack) + '\n'
		<< "Defense: " + to_string(firespirit1->Defense) + '\n' << endl;

	cout << "Cost: " + to_string(pyromaniac1->Cost) + '\n'
		 << "Name: " + pyromaniac1->Name + '\n'
		 << "Description: " + pyromaniac1->Description + '\n'
		 << "Attack: " + to_string(pyromaniac1->Attack) + '\n'
		 << "Defense: " + to_string(pyromaniac1->Defense) + '\n' << endl;

	//Some bizzare behaviour when adding a char to the end of a string
	//Im new to c++ okay
	cout << "Fire Spirit attacks Pyromaniac!\n" << endl;
	firespirit1->Soul::Attacking(pyromaniac1);

	cout << "Cost: " + to_string(pyromaniac1->Cost) + '\n'
		<< "Name: " + pyromaniac1->Name + '\n'
		<< "Description: " + pyromaniac1->Description + '\n'
		<< "Attack: " + to_string(pyromaniac1->Attack) + '\n'
		<< "Defense: " + to_string(pyromaniac1->Defense) + '\n' << endl;

	Deck player1Deck;
	player1Deck.Add(firespirit1);
	player1Deck.Add(firespirit2);

	player1Deck.Add(pyromaniac1);
	player1Deck.Add(pyromaniac2);

	player1Deck.Add(hellhound1);
	player1Deck.Add(hellhound2);

	player1Deck.Add(hellsparkmutt1);
	player1Deck.Add(hellsparkmutt2);

	player1Deck.Shuffle();

	Player* player1 = new Player();
	player1->Deck = player1Deck;

	Player* player2 = new Player();
	player2->UserName = "Maspe36";
	//Draw a card
	auto temp = (player1->Deck.Draw());

	Soul *SoulCard = nullptr;
	//Type2 *t2 = nullptr;
	//Type3 *t3 = nullptr;

	if (SoulCard = dynamic_cast<Soul*>(temp))
	{
		cout << SoulCard->Name << " is attacking " << player2->UserName << " for " << SoulCard->Attack << "!" << endl;
		SoulCard->Attacking(player2);
		cout << player2->Health << endl;
	}
	// if (t2 = dynamic_cast<Type2*>(p))
	//{
	//t2->type2Method();
	//}
	//else if (t3 = dynamic_cast<Type3*>(p))
	//{
	//t3->type3Method();
	//}



    return 0;
}

