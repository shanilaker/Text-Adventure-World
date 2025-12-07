#pragma once
#include <iostream>
#include <string.h>
#include "Riddle.h"
#include "Game.h"
#include "Door.h"
#include "Bomb.h"
#include "Switch.h"

using std::cout, std::endl;

class Player;
class Screen 
{
public:
	enum { MAX_SWITCHES = 10 };
private:
	Riddle screen_riddle;
	char screen[Game::MAX_Y][Game::MAX_X + 1];
	char screen_reset[Game::MAX_Y][Game::MAX_X + 1];
	Door screen_door;
	int players_moved = 0;
	int default_x;
	int default_y;
	Bomb screen_bomb;
	Switch screen_switches[MAX_SWITCHES];
	int num_switches = 0;
	int required_on_switches;

public:
	//Empty ctor
	Screen();

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door the_screen_door, int the_default_x, int the_default_y, Bomb the_screen_bomb, const Switch the_switches[], int count, int required_on);

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y]);

	//Get the screen riddle
	Riddle& getScreenRiddle(){ return screen_riddle; }

	//Reset the screen
	void reset();
	
	//Draw the all screen
	void draw() const;

	//Draws a specific location on the screen
	void draw(int x, int y) const;

	//Set the char at this location
	void setCharAt(int x, int y, char ch);

	//Get the char at this location
	char getCharAt(int x, int y) const;

	//Set the door at this location
	Door& getDoor(){ return screen_door; }

	//Get the default x
	int& getDefault_x() { return default_x; }

	//Get the default y
	int& getDefault_y(){ return default_y; }

	//Get the number of players that moved
	int& get_players_moved() { return players_moved; }

	//Set the number of players that moved
	void set_player_moved(){ players_moved++; }

	//Get the bomb
	Bomb& get_bomb() { return screen_bomb; }

	//Get the switches
	Switch* getSwitches() { return screen_switches; }

	//Get the number of switches
	int getNumSwitches() const { return num_switches; }

	//Get the number of switches that need to be on
	int getRequiredOnSwitches() const { return required_on_switches; }

	//Checks if the switches is on
	bool areSwitchesCorrect() const;
};


