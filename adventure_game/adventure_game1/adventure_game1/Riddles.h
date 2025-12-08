#pragma once
#include "Riddle.h"
#include "Game.h"

class Riddles
{
	Riddle game_riddles[3];

public:
	//Get the game_riddles
	Riddle* getgame_riddles() { return game_riddles; }

	//Set the game_riddles
	void setgame_riddles(Riddle r , int i) { game_riddles[i] = r; }

	//Empty ctor
	Riddles();
};

