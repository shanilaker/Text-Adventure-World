#pragma once
#include <iostream>
#include "utils.h"
#include "Direction.h"
#include "Game.h"
#include "Key.h"

class Screens;
class Screen;

class Player {
	int x = 1, y = 1;
	int diff_x = 0, diff_y = 0;
	char ch = '*';
	static constexpr size_t NUM_KEYS = 6;
	char held_item = '\0';
	char keys[NUM_KEYS];
	int current_room_id = 0;
	//int held_key;
	bool just_disposed = false;
	bool is_active = true;
	int reset_valueX;
	int reset_valueY;
	int diff_valueX;
	int diff_valueY;
public:
	int solvedRiddle = -2;
	Player() {}
	Player(int x1, int y1, int diffx, int diffy, char c, const char(&the_keys)[NUM_KEYS + 1], int room_id, int riddleSolved) {
		x = x1;
		y = y1;
		diff_x = diffx;
		diff_y = diffy;
		ch = c;
		memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
		current_room_id = room_id;
		riddleSolved = solvedRiddle;
		reset_valueX = x1;
		reset_valueY = y1;
		diff_valueX = diffx;
		diff_valueY = diffy;
	}

	void reset()
	{
		x = reset_valueX;
		y = reset_valueY;
		diff_x = diff_valueX;
		diff_y = diff_valueY;
		held_item = '\0';
		is_active = true;
		current_room_id = 1;
		solvedRiddle = -2;
	}
	void draw() {
		if (is_active)
		{
			draw(ch);
		}
	}
	void draw(char c) {
		if (is_active) {
			gotoxy(x, y);
			std::cout << c;
		}
	}
	bool isActive() const { return is_active; }
	void kill() { 
		draw(' ');
		is_active = false; }
	bool move(Screen& cur_screen, Game the_game);
	void setDirection(Direction dir);
	void handleKeyPressed(char key_pressed);
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	
	int getCurrentRoomID() const {
		return current_room_id;
	}
	/*void setKey(int the_key)
	{
		held_key = the_key;
	}*/
	
	void setPosition(int x1, int y1)
	{
		x = x1;
		y = y1;
		setDirection(Direction::STAY);
	}

	void setCurrentRoomID(int new_room_id) {
		current_room_id = new_room_id;
	}

	void hideForTransition()
	{
		x = -1;
		y = -1;
		setDirection(Direction::STAY);
	}

	bool isWaiting()const
	{
		return x == -1 && y == -1;
	}

	int getDiffx() const {
		return diff_x;
	}

	int getDiffy() const {
		return diff_y;
	}

	void setJustDisposed(bool val) { just_disposed = val; }
	bool getJustDisposed() const { return just_disposed; }
	char getHeldItem() const { return held_item; }
	void setHeldItem(char item) { held_item = item; }
	bool hasItem() const { return held_item != '\0'; }
	bool getIsActive()
	{
		return is_active;
	}
};

