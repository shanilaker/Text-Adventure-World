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
		for (int i = 0; i < MAX_Y; i++)
		{
			screen[i] = nullptr;
		}
	}
	Screen(const char* the_screen[MAX_Y]);
	Screen(const Screen& other); // Copy Constructor
	Screen& operator=(const Screen& other);

	//char getCharAt(const Player& p) const {
		//return screen[p.getY()][p.getX()];
		//}
	void draw() const;
	//bool isWall(const Player& p) const {
	//	return getCharAt(p) == '#';//to change
	//}

	~Screen();
};


