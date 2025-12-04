#pragma once
#include <iostream>
#include "utils.h"
#include "Direction.h"
#include "Game.h"

class Screens;
class Screen;

class Player {
	int x = 1, y = 1;
	int diff_x = 1, diff_y = 0;
	char ch = '*';
	static constexpr size_t NUM_KEYS = 6;
	char held_item = '\0';
	char keys[NUM_KEYS];
	int current_room_id = 0;
	

public:
	int solvedRiddle = 0;
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
	}
	void draw() {
		draw(ch);
	}
	void draw(char c) {
		gotoxy(x, y);
		std::cout << c;
	}
	bool move(Screen& cur_screen);
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

	
	void setCurrentRoomID(int new_room_id) {
		current_room_id = new_room_id;
	}

	char getHeldItem() const { return held_item; }
	void setHeldItem(char item) { held_item = item; }
	bool hasItem() const { return held_item != '\0'; }
};

