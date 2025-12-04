#pragma once
#include <iostream>
#include "Player.h"
#include <string.h>
#include "Riddle.h"
#include "Game.h"

using std::cout, std::endl;


class Screen {
	Riddle screen_riddle;
private:
	char* screen[Game::MAX_Y];
public:
	Screen()
	{
		for (int i = 0; i < Game::MAX_Y; i++)
		{
			screen[i] = nullptr;
		}
	}
	Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle);
	Screen(const char* the_screen[Game::MAX_Y]);
	Screen(const Screen& other); // Copy Constructor
	Screen& operator=(const Screen& other);
	const Riddle& getScreenRiddle() const 
	{ 
		return screen_riddle; 
	}
	//char getCharAt(const Player& p) const {
		//return screen[p.getY()][p.getX()];
		//}
	void draw() const;
	//bool isWall(const Player& p) const {
	//	return getCharAt(p) == '#';//to change
	//}
	void setCharAt(int x, int y, char ch);
	char getCharAt(int x, int y) const;
	~Screen();
};


