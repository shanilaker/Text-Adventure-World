#pragma once
class Bomb
{
	bool is_activated = false;
	int x;
	int y;
public:
	Bomb(bool bomb_activated, int the_x, int the_y) :is_activated(bomb_activated), x(the_x), y(the_y)
	{ }

	Bomb()
	{

	}
};

