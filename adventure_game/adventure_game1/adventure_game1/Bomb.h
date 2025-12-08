#pragma once
class Screen;
class Game;
class Player;

class Bomb
{
	bool is_activated = false;
	int x = -1;
	int y = -1;
	int time_to_explode = -1;
	bool is_active = true;

public:
	//Ctor
	Bomb(bool bomb_activated, int the_x, int the_y, int initial_time) :is_activated(bomb_activated), x(the_x), y(the_y), time_to_explode(initial_time), is_active(true) {}

	//Empty ctor
	Bomb(){}

	//Set is active
	void setisActive(bool value){ is_active = value; }

	//Set is activated
	void set_is_activated(bool set_to){ is_activated = set_to; }

	//Set x
	void setX(int newX){ x = newX; }

	//Return if the bomb is activated
	bool is_bomb_activated() const{ return is_activated; }

	//Set y
	void setY(int newY){ y = newY; }

	//Get x
	int getX() const{ return x; }

	//Get y
	int getY() const{ return y; }

	//Set the time to explode
	void set_time_to_explode(int time){ time_to_explode = time + 5; }

	//Get the time to explode
	int get_time_to_explode() const{ return time_to_explode; }

	//Deactivate the bomb
	void kill() { is_active = false; }

	void explodeBomb(Screen& cur_screen, Game& the_game, int& game_state, Player(&players)[2]);
};

