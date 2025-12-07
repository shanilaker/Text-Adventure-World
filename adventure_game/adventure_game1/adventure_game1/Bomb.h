#pragma once
class Bomb
{
	bool is_activated = false;
	int x;
	int y;
	int time_to_explode;
	bool is_active = true;
public:
	//Ctor
	Bomb(bool bomb_activated, int the_x, int the_y, int initial_time) :is_activated(bomb_activated), x(the_x), y(the_y), time_to_explode(initial_time), is_active(true) {}

	//Empty ctor
	Bomb(){}
	void setisActive(bool value)
	{
		is_active = value;
	}
	void set_is_activated(bool set_to)
	{
		is_activated = set_to;
	}
	void setX(int newX)
	{
		x = newX;
	}
	bool is_bomb_activated() const
	{
		return is_activated;
	}
	void setY(int newY)
	{
		y = newY;
	}
	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
	void set_time_to_explode(int time)
	{
		time_to_explode = time + 5;
	}
	int get_time_to_explode() const
	{
		return time_to_explode;
	}
	void kill() { is_active = false; }
};

