#pragma once
#include <vector>

using namespace std;

class Player;
class Card;
class Action;

class GameState
{
public:
	GameState(vector<Player*> Players);
	vector<Player*> PlayersInGame;
	Player* ActivePlayer;
	vector<Card*> CardOrder; 
	~GameState();

	void Start();
	void MulliganState();
	void PlayState();
	void ChangeActivePlayer();
	void PlayCard(Player * CardOwner, int HandIndex);
	void CheckEffects(Action * CurrentAction);
};

