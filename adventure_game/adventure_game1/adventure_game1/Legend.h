#pragma once
#include "Point.h"
#include "Game.h"


class Screen;
class Legend
{
	Point p;
	bool over_the_screen = false;
	char l_screen[Game::MAX_Y][Game::MAX_X + 1];
	bool on_objects = false;

public:

	//Empty ctor
	Legend();

	//Ctor
	//Legend(Point _p, const char* _incoming_screen[Game::MAX_Y]);
	Legend(Point _p, const char _incoming_screen[Game::MAX_Y][Game::MAX_X + 1]);

	//Get point
	Point getPoint() const { return p; }

	//Draw the legend
	void draw(char board [Game::MAX_Y][Game::MAX_X + 1], vector<Player>& players);

	//Get if over_the_screen
	bool get_over_the_screen() const { return over_the_screen; }

	//Get if on_objects
	bool get_on_objects() const { return on_objects; }

	//Update the legend values
	void update_values(char ch, vector<Player>& players);
};

