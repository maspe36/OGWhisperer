#pragma once
#include <vector>

/* At some point there will
   probably need to be a unique
   hash in all objects for each game */

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
private:
	string delemiter = ":";
};

