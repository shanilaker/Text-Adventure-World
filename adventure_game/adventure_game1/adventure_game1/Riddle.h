#pragma once
#include "Game.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Player.h"
#include <string.h>

using std::cout, std::endl, std::vector;


class Riddle
{
	int x = 0;
	int y = 0;
	char text[Game::MAX_Y][Game::MAX_X + 1] = {};
	int room_connected = -1;
	char answer = -1;
	bool is_active = true;
	bool activated = false;
public:

	//Ctor
	Riddle(const char* r_text[Game::MAX_Y], int r_x, int r_y, int r_room_connected, char the_answer);
	
	//Empty Ctor
	Riddle();

	//Show the riddle on the screen
	void Show_Riddle() const;

	//Get is active
	bool getisActive() const { return is_active; }

	//Get activated
	bool getActivated() const { return activated; }

	//Set activated
	void setActivated(bool value) { activated = value; }

	//Reset riddle
	void reset();

	//Deactivates the riddle
	void kill() { is_active = false; }

	//Get the x
	int getX() const { return x; }

	//Get the y
	int getY() const { return y; }

	//Set the x
	int setX() const { return x; }

	//Set the y
	int setY() const { return y; }

	//Get the answer of the riddle
	char getAnswer() const { return answer; }

	//Set the is_active
	void setisActive(const bool& value) { is_active = value; }

	//Check if player's riddle answer is correct and update game accordingly
	static void checkRiddleAnswer(Screen& cur_screen, Game& the_game, char key, vector<Player>& players); 
};

