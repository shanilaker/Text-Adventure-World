#pragma once
#include "Screen.h"
#include "Riddles.h"
#include "Bomb.h"
#include "Game.h"

class Screens
{
	Screen game_screens[7];

public:

	//Get the game_screens
	Screen(&getgame_screens())[7] { return game_screens; }

	//Set the game_screens
	void setgame_screens(Screen s, const int& i) { game_screens[i] = s; }

	//Empty Ctor
	Screens();

	//Get all the file names of the screens
	void getAllScreenFileNames(std::vector<std::string>& vec_to_fill);

	//Count number of riddles at the game
	size_t getTotalRiddlesCount();
};

