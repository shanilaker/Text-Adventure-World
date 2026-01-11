#pragma once
#include "utils.h"
#include <iostream>
#include "Direction.h"
#include "Game.h"


class Screen;
class Obstacle
{
	int x = 1, y = 1;
	int diff_x = 0, diff_y = 0;
	int r_x = 1, r_y = 1;
	int force_needed = 1;
	int reset_force_needed = 1;
	bool is_moved = false;
	Direction wanted_d = Direction::STAY;
	vector<Point> body;
	vector<Point> r_body;

public:

	//Empty ctor
	Obstacle() {}

	//Ctor
	Obstacle(int _x, int _y, int _diff_x, int _diff_y,int _force_needed,vector<Point> _body) :x(_x), y(_y), diff_x(_diff_x), diff_y(_diff_y), r_x(x), r_y(y), force_needed(_force_needed), reset_force_needed(_force_needed), body(_body), r_body(body){}

	//Get the force
	int get_force_needed() const { return force_needed; }

	//Get the body
	vector<Point>& get_body() { return body; }

	//Get the reset force
	int get_reset_force() const { return reset_force_needed; }

	//Set the reset force
	void set_reset_force(int value) { reset_force_needed = value; }

	//If this is in the length of the body
	bool occupies(int x, int y) const;

	//Reset the obstacle
	void reset();

	//Get the x
	int getX() const { return x; }

	//Set the wanted_d
	void set_wanted_d(Direction value) { wanted_d = value; }

	//Set the diff_x
	void set_diff_x(int value) { diff_x = value; }

	//Set the diff_y
	void set_diff_y(int value) { diff_y = value; }

	//Get the wanted_d
	Direction get_wanted_d() const { return wanted_d; }

	//Get the y
	int getY() const { return y; }

	//Set the is_moved
	void set_is_moved(bool value) { is_moved = value; }

	//Get diff_x
	int getDiffX() const { return diff_x; }

	//Get diff_y
	int getDiffY() const { return diff_y; }

	//Get the is_moved
	bool get_is_moved() const { return is_moved; }

	//Set the force
	void set_force_needed(int input_force) { force_needed -= input_force; }

	//Set to the force
	void set_to_force_needed(int force) { force_needed = force; }

	//Draw c in x, y
	void draw(const char& c) const;

	//Set the obstacle's direction
	void setDirection(Direction dir);

	//Move the obstacle
	void move(Screen& cur_screen, vector<Player>& players);

	//If (_x,_y) is in the body of the obstacle
	bool in_body(int _x, int _y);

	//Save the Obstacle state
	void save(std::ostream& out) const;

	//Load the Obstacle state
	void load(std::istream& in);
};

