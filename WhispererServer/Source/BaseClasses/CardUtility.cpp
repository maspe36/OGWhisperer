#include "CardUtility.h"
#include "BaseClasses.h"
#include <boost/algorithm/string.hpp>
#include <sstream>

CardUtility::CardUtility()
{
}

bool CardUtility::IsColorCreaturePresent(GameState * CurrentGame, Card::_Color Color)
{
	for (auto i : CurrentGame->PlayersInGame)
	{
		for (auto s : i->CreaturesInPlay) {
			if (s->Color == Color)
			{
				return true;
			}
		}
	}
	return false;
}

vector<string> CardUtility::GetUserCreatureTarget()
{
	cout << "Select a creature target..." << endl;
	// Now we take input and depending on what it is set action object.
	string ClientInput;
	getline(cin, ClientInput);

	vector<string> Parts;
	// Need to use the same string from gamestate.
	boost::split(Parts, ClientInput, boost::is_any_of(":"));

	return Parts;
}

vector<string> CardUtility::GetUserCreatureOrPlayerTarget()
{
	cout << "Select a creature or player target..." << endl;
	// Now we take input and depending on what it is set action object.
	string ClientInput;
	getline(cin, ClientInput);

	vector<string> Parts;
	// Need to use the same string from gamestate.
	boost::split(Parts, ClientInput, boost::is_any_of(":"));

	return Parts;
}

CardUtility::~CardUtility()
{
}
