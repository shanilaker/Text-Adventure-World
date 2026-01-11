#pragma once
#include "Riddle.h"
#include "Game.h"

class Riddles
{
	vector<Riddle> game_riddles;

public:

	//Get the game_riddles
	vector<Riddle>& getgame_riddles() { return game_riddles; }
	 
	//Set the game_riddles
	void setgame_riddles(Riddle r) { game_riddles.push_back(r); }

	//Empty ctor
	Riddles();

	//Get all the file names of the riddles
	void getAllRiddleFileNames(std::vector<std::string>& vec_to_fill);
};

