#pragma once
#include "Screen.h"
#include "Riddles.h"
#include "Bomb.h"
#include "Game.h"

class Screens
{
	vector<Screen> game_screens;
	int total_riddle_screens_loaded = 0;

public:

	//Get the game_screens
	vector<Screen>& getgame_screens() { return game_screens; }

	//Set the game_screens
	void setgame_screens(Screen s, const int& i) { game_screens[i] = s; }

	//Empty Ctor
	Screens();

	//Get all the file names of the screens
	void getAllScreenFileNames(std::vector<std::string>& vec_to_fill);

	//Count number of riddles at the game
	size_t getTotalRiddlesCount();

	int getTotalRiddleScreensCount() const { return total_riddle_screens_loaded; }
};

