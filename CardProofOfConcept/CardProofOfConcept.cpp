// CardProofOfConcept.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include "Fire_Spirit.h"
#include "Pyromaniac.h"

int main()
{
	Fire_Spirit firespirit;
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

	firespirit.Soul::Attacking(pyromaniac);

	cout << "Cost: " + to_string(pyromaniac.Cost) + '\n'
		<< "Name: " + pyromaniac.Name + '\n'
		<< "Description: " + pyromaniac.Description + '\n'
		<< "Attack: " + to_string(pyromaniac.Attack) + '\n'
		<< "Defense: " + to_string(pyromaniac.Defense) + '\n' << endl;

    return 0;
}

