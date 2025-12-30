#pragma once
#include <iostream>
#include <string.h>
#include "Riddle.h"
#include "Game.h"
#include "Door.h"
#include "Bomb.h"
#include "Switch.h"
#include"Obstacle.h"
#include "Legend.h"
#include "Spring.h"

using std::cout, std::endl;


class Player;
class Screen 
{
public:
	enum { MAX_SWITCHES = 10 };
	enum { MAX_SPRINGS = 5 };
private:
	//Riddle screen_riddle;
	char screen[Game::MAX_Y][Game::MAX_X + 1];
	char screen_reset[Game::MAX_Y][Game::MAX_X + 1];
	Door screen_door;
	int players_moved = 0;
	int default_x = -1;
	int default_y = -1;
	Switch screen_switches[MAX_SWITCHES];
	int num_switches = 0;
	Legend screen_legend;
	vector<Bomb> bombs;
	vector<Obstacle> obstacles;
	vector<Riddle> riddles;
	Spring screen_springs[MAX_SPRINGS];
	int num_springs = 0;
	bool is_dark = false;
public:
	//Empty ctor
	Screen();

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y], Door the_screen_door, int the_default_x, int the_default_y, const Switch the_switches[], int count, Legend _screen_legend, vector<Bomb>& _bombs, vector<Obstacle>& _obstacles, vector<Riddle>& _riddles, const Spring the_springs[], int spring_count);

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y]);

	//Get the screen riddle
	vector<Riddle>& get_riddles(){ return riddles; }

	//Reset the screen
	void reset(vector<Player>& players);
	
	//Draw the all screen
	void draw() const;

	//Get the springs
	Spring* getSprings() { return screen_springs; }

	// Get the number of springs
	int getNumSprings() const { return num_springs; }

	// Set springs back after spring activated
	void restoreSprings();

	// Get the spring at specific point
	Spring* getSpringAt(int x, int y);

	// Set screen as dark
	void setIsDark(bool val) { is_dark = val; }

	// Check if screen is dark
	bool getIsDark() const { return is_dark; }

	// Draw screen as dark
	void drawDark(vector<Player>& players) const;

	//Draws a specific location on the screen
	void draw(const int& x, const int& y) const;

	//Set the char at this location
	void setCharAt(const int& x, const int& y, const char& ch);

	//Get the char at this location
	char getCharAt(const int& x, const int& y) const;

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

	//Get the obstacles
	vector<Obstacle>& get_obstacles() { return obstacles; }

	//Get the bombs
	vector<Bomb>& get_bombs() { return bombs; }


	//Get the switches
	Switch* getSwitches() { return screen_switches; }

	//Get the number of switches
	int getNumSwitches() const { return num_switches; }

	//Get the screen legend
	Legend& get_screen_legend() { return screen_legend; }


	//Checks if the switches is on
	bool areSwitchesCorrect() const;


	//Load the screen from a file
	void load(const std::string& filename, int index);
};


