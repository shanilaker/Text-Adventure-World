#pragma once
#include "Game.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Player.h"
#include <string.h>

using std::cout, std::endl;

class Riddle
{
	int x = 0;
	int y = 0;
	const char* text[Game::MAX_Y] = {};
	int room_connected = -1;
	char answer;

public:
	Riddle(const char* r_text[Game::MAX_Y], int r_x, int r_y, int r_room_connected, char the_answer);
	Riddle();
	Riddle(const Riddle& other);
	~Riddle();
	Riddle& operator=(const Riddle& other);
	void draw() const;
	void Show_Riddle() const;

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	char getAnswer() const {
		return answer;
	}
};

