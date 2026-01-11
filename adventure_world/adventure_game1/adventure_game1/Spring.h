#pragma once
#include "Direction.h"
#include <iostream>

class Spring {
	int x = -1;
	int y = -1;
	int length = 1;
	Direction dir = Direction::STAY;

public:
	// Empty ctor
	Spring() {};

	// Ctor
	Spring(int _x, int _y, int len, Direction _dir) : x(_x), y(_y), length(len), dir(_dir) {};

	// Get the x
	int getX() const { return x; }

	// Get the y
	int getY() const { return y; }

	// Get the length of spring
	int getLength() const { return length; }

	// Get the direction of spring
	Direction getDir() const { return dir; }

	// Check if spring is at (x,y)
	bool isSpringAt(int test_x, int test_y) const;

	//Save the Spring state
	void save(std::ostream& out) const {out << x << " " << y << " " << length << " " << (int)dir << std::endl;}

	//Load the Spring state
	void load(std::istream& in);
};


