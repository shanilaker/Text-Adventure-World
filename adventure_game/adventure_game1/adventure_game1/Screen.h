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
class Screen {

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
	Screen()
	{
		for (int i = 0; i < Game::MAX_Y; i++)
		{
			for (int j = 0; j < Game::MAX_X; j++)
			{
				screen[i][j] = ' ';
				screen_reset[i][j] = ' ';
			}
		}

	}
	Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door the_screen_door, int the_default_x, int the_default_y, Bomb the_screen_bomb, const Switch the_switches[], int count, int required_on);
	Screen(const char* the_screen[Game::MAX_Y]);
	//Screen(const Screen& other); // Copy Constructor
	//Screen& operator=(const Screen& other);
	Riddle& getScreenRiddle()  
	{ 
		return screen_riddle; 
	}
	void reset()
	{
		for (int i = 0; i < Game::MAX_Y; i++)
		{
			for (int j = 0; j < Game::MAX_X; j++)
			{
				screen[i][j] = screen_reset[i][j];
			}
		}
		screen_riddle.setisActive(true);
		screen_door.setisActive(true);
		screen_bomb.setisActive(true);
		screen_bomb.set_is_activated(false);
		screen_bomb.set_time_to_explode(-6);
		players_moved = 0;
		for (int i = 0;i< num_switches;i++)
		{
			screen_switches[i].set_is_on();
		}
		screen_door.set_num_key_needed();
		screen_door.set_is_open();
	}
	void draw() const;
	void draw(int x, int y) const;
	void setCharAt(int x, int y, char ch);
	char getCharAt(int x, int y) const;
	Door& getDoor()
	{
		return screen_door;
	}
	int& getDefault_x()
	{
		return default_x;
	}
	int& getDefault_y()
	{
		return default_y;
	}
	//~Screen();
	int& get_players_moved()
	{
		return players_moved;
	}
	void set_player_moved()
	{
		players_moved++;
	}
	Bomb& get_bomb()
	{
		return screen_bomb;
	}

	Switch* getSwitches() { return screen_switches; }
	int getNumSwitches() const { return num_switches; }
	int getRequiredOnSwitches() const { return required_on_switches; }

	bool areSwitchesCorrect() const {
		int count = 0;
		for (int i = 0; i < num_switches; i++) {
			if (screen_switches[i].isOn()) {
				count++;
			}
		}
		return count == required_on_switches;
	}
};


