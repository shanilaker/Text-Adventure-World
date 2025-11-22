#pragma once
#include <iostream>
#include "Player.h"
#include <string.h>

using std::cout, std::endl;


class Screen {
public:
	enum { MAX_X = 80, MAX_Y = 25 };
private:
	const char* screen[MAX_Y];
public:
	Screen()
	{
	}
	Screen(const char* the_screen[MAX_Y])
	{
		memcpy(screen, the_screen, sizeof(MAX_Y));//need deep copy!
	}

	//char getCharAt(const Player& p) const {
		//return screen[p.getY()][p.getX()];
		//}
	void draw() const;
	//bool isWall(const Player& p) const {
	//	return getCharAt(p) == '#';//to change
	//}
};


