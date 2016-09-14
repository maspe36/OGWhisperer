#pragma once
#include <vector>
#include <string>

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
	
	static const char delmchar = ':';
	const string delemiter = ":";
	static const char PlayerProto = 'p';
	static const char CardProto = 'c';
	static const char ConstantProto = 't';
	static const char SoulProto = 's';
	static const char SwiftProto = 'w';
	static const char EndTurnProto = 'e';
	static const char AttackProto = 'a';

	~GameState();

	static bool IsConstantDeadMessage(Card* Target);
	static bool IsDeadMessage(Card* Target);
	static bool IsDead(Card* Target);
	static bool IsPlayerDead(Player* Target);

	void Start();
	void MulliganState();
	void DrawTill5();
	void TurnStartMaintenance();
	void PlayState();
	void EndGameState();
	void ChangeActivePlayer();
	void PlayCard(Card* Target);
	void CheckEffects(Action * CurrentAction);
	void ClearDeadCards();
	void ClearDeadPlayers();
	bool IsGameOver();
};