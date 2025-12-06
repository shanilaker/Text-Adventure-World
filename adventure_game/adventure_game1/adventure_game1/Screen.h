#pragma once
#include <iostream>
#include <string.h>
#include "Riddle.h"
#include "Game.h"
#include "Door.h"
#include "Bomb.h"

using std::cout, std::endl;

class Player;
class Screen {
	Riddle screen_riddle;
	char* screen[Game::MAX_Y];
	Door screen_door;
	int players_moved = 0;
	int default_x;
	int default_y;
	Bomb screen_bomb;

public:
	Screen()
	{
		for (int i = 0; i < Game::MAX_Y; i++)
		{
			screen[i] = nullptr;
		}

	}
	Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door screen_door, int default_x,int default_y, Bomb screen_bomb);
	Screen(const char* the_screen[Game::MAX_Y]);
	Screen(const Screen& other); // Copy Constructor
	Screen& operator=(const Screen& other);
	const Riddle& getScreenRiddle() const 
	{ 
		return screen_riddle; 
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
	~Screen();
	int& get_players_moved()
	{
		return players_moved;
	}
	void set_player_moved()
	{
		players_moved++;
	}
};


