#include "stdafx.h"
#include <string>
#include <vector>
#include "Cards.h"
#include "GameState.h"
#include "Player.h"

int main()
{
	// I want a factory...
	// How should I do this part? This seems complex
	// I could do the CardFactory method where I create a new Card* from the specific cards class
	// Then it fits into my game structure
	vector<Card*> genericDeck1;
	vector<Card*> genericDeck2;
	vector<Card*> genericDeck3;

	Card* foo1 = NULL;
	Card* foo2 = NULL;
	Card* foo3 = NULL;

	Kindling kindling11;
	Kindling kindling12;
	Kindling kindling13;
	foo1 = &kindling11;
	foo2 = &kindling12;
	foo3 = &kindling13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Kindling kindling21;
	Kindling kindling22;
	Kindling kindling23;
	foo1 = &kindling21;
	foo2 = &kindling22;
	foo3 = &kindling23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Spark_Mouse sparkmouse11;
	Spark_Mouse sparkmouse12;
	Spark_Mouse sparkmouse13;
	foo1 = &sparkmouse11;
	foo2 = &sparkmouse12;
	foo3 = &sparkmouse13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Spark_Mouse sparkmouse21;
	Spark_Mouse sparkmouse22;
	Spark_Mouse sparkmouse23;
	foo1 = &sparkmouse21;
	foo2 = &sparkmouse22;
	foo3 = &sparkmouse23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Fire_Spirit firespirit11;
	Fire_Spirit firespirit12;
	Fire_Spirit firespirit13;
	foo1 = &firespirit11;
	foo2 = &firespirit12;
	foo3 = &firespirit13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Fire_Spirit firespirit21;
	Fire_Spirit firespirit22;
	Fire_Spirit firespirit23;
	foo1 = &firespirit21;
	foo2 = &firespirit22;
	foo3 = &firespirit23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Pyromaniac pyromaniac11;
	Pyromaniac pyromaniac12;
	Pyromaniac pyromaniac13;
	foo1 = &pyromaniac11;
	foo2 = &pyromaniac12;
	foo3 = &pyromaniac13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Pyromaniac pyromaniac21;
	Pyromaniac pyromaniac22;
	Pyromaniac pyromaniac23;
	foo1 = &pyromaniac21;
	foo2 = &pyromaniac22;
	foo3 = &pyromaniac23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Hellhound hellhound11;
	Hellhound hellhound12;
	Hellhound hellhound13;
	foo1 = &hellhound11;
	foo2 = &hellhound12;
	foo3 = &hellhound13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Hellhound hellhound21;
	Hellhound hellhound22;
	Hellhound hellhound23;
	foo1 = &hellhound21;
	foo2 = &hellhound22;
	foo3 = &hellhound23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Hellspark_Mutt hellsparkmutt11;
	Hellspark_Mutt hellsparkmutt12;
	Hellspark_Mutt hellsparkmutt13;
	foo1 = &hellsparkmutt11;
	foo2 = &hellsparkmutt12;
	foo3 = &hellsparkmutt13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Hellspark_Mutt hellsparkmutt21;
	Hellspark_Mutt hellsparkmutt22;
	Hellspark_Mutt hellsparkmutt23;
	foo1 = &hellsparkmutt21;
	foo2 = &hellsparkmutt22;
	foo3 = &hellsparkmutt23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Pyrophile pyrophile11;
	Pyrophile pyrophile12;
	Pyrophile pyrophile13;
	foo1 = &pyrophile11;
	foo2 = &pyrophile12;
	foo3 = &pyrophile13;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	Pyrophile pyrophile21;
	Pyrophile pyrophile22;
	Pyrophile pyrophile23;
	foo1 = &pyrophile21;
	foo2 = &pyrophile22;
	foo3 = &pyrophile23;
	genericDeck1.push_back(foo1);
	genericDeck2.push_back(foo2);
	genericDeck3.push_back(foo3);

	// New players need a deck and a name
	Player* player1 = new Player("Sam", genericDeck1);
	Player* player2 = new Player("Ben", genericDeck2);
	Player* player3 = new Player("Nick", genericDeck3);

	vector<Player*> Players = { player1, player2, player3 };
	//vector<Player*> Players = { player1, player2 };

	GameState* myGame = new GameState(Players);

	myGame->Start();

	return 0;
}
