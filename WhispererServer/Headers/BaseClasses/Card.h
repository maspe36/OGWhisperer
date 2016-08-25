#pragma once
#include <iostream>
#include <vector>

/* At some point there will
   probably need to be a unique
   hash in all objects for each game */

using namespace std;

class GameState;
class Action;
class Player;

class Card
{
public:
	 /* Order of colors in cost vector (Alphabetical)
	    0: Dark
	    1: Earth
		2: Fire
		3: Light
		4: Water
		5: Wind */
	vector<int> Cost;
	// Name of the card
	string Name;
	// The flavour text of a card
	string FlavourText;
	// The effect of a card in text
	string EffectText;
	// The color of a card
	enum _Color 
	{
		Dark,
		Earth,
		Fire,
		Light,
		Water,
		Wind
	} Color;
	// Base Card Types
	enum _CardType 
	{
		Constant,
		Soul, 
		Swift
	} CardType;
	// Different possible effect types
	enum _EffectType
	{
		Continuous,
		Downfall, 
		HighTide,
		InHand,
		Introduce,
		None, 
		OnDiscard,
		OnDraw, 
		Rush, 
		Statis, 
		Trigger
	} EffectType;

	vector<_EffectType> Effects;
	Player* Owner;

	string ToString();
	virtual void Effect(GameState* CurrentGame);
	virtual bool IsEffectTriggered(Action* CurrentAction);

	Card(vector<int> Cost, string Name, string EffectText, string FlavourText, 
		_Color Color, _CardType CardType, vector<_EffectType> Effects);	
	virtual ~Card();
};
