#pragma once
#include <string.h>
#include <vector>

class Screen;
class Game;
class Player;


using std::vector;
class Bomb
{
	bool is_activated = false;
	int x = -1;
	int y = -1;
	int r_x = -1;
	int r_y = -1;
	int time_to_explode = -1;
	bool is_active = true;

public:
	//Ctor
	Bomb(bool bomb_activated, int the_x, int the_y, int initial_time) :is_activated(bomb_activated), x(the_x), y(the_y), time_to_explode(initial_time), is_active(true),r_x(the_x), r_y(the_y) {}

	//Empty ctor
	Bomb(){}

	//Set is active
	void setisActive(const bool& value){ is_active = value; }

	//Set is activated
	void set_is_activated(const bool& set_to, const int& x1, const int& y1);

	//Set x
	void setX(const int& newX){ x = newX; }

	//Reset the bomb
	void reset();

	//Return if the bomb is activated
	bool is_bomb_activated() const{ return is_activated; }

	//Set y
	void setY(const int& newY){ y = newY; }

	//Get x
	int getX() const{ return x; }

	//Get y
	int getY() const{ return y; }

	//Set the time to explode
	void set_time_to_explode(const int& time){ time_to_explode = time + 5; }

	//Get the time to explode
	int get_time_to_explode() const{ return time_to_explode; }

	//Deactivate the bomb
	void kill(Screen& current_screen, const int& bomb_x, const int& bomb_y);

	//Explode the bomb
	void explodeBomb(Screen& cur_screen, Game& the_game, int& game_state, vector<Player>& players);  
};

