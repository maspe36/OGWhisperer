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
	int ActiveIndex;
	vector<Card*> CardOrder;

	const string delemiter = ":";
	static const char PlayerProto = 'p';
	static const char CardProto = 'c';
	static const char SoulProto = 's';
	static const char EndTurnProto = 'e';
	static const char AttackProto = 'a';

	~GameState();

	static bool IsDeadMessage(Card* Target);
	static bool IsDead(Card* Target);
	static bool IsPlayerDead(Player* Target);

	void Start();
	void MulliganState();
	void PlayState();
	void ChangeActivePlayer();
	void PlayCard(int PlayerIndex, int HandIndex);
	void CheckEffects(Action * CurrentAction);
	void ClearDeadCards();
	void ClearDeadPlayers();
	bool IsGameOver();
};