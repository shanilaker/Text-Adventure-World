#pragma once
#include <iostream>
#include "utils.h"
#include "Direction.h"

class Player {
	int x = 1, y = 1;
	int diff_x = 1, diff_y = 0;
	char ch = '*';
	static constexpr size_t NUM_KEYS = 5;
	char keys[NUM_KEYS];

public:
	Player() {}
	Player(int x1, int y1, int diffx, int diffy, char c, const char(&the_keys)[NUM_KEYS + 1]) {
		x = x1;
		y = y1;
		diff_x = diffx;
		diff_y = diffy;
		ch = c;
		memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
	}
	void draw() {
		draw(ch);
	}
	void draw(char c) {
		gotoxy(x, y);
		std::cout << c;
	}
	void move();
	void setDirection(Direction dir);
	void handleKeyPressed(char key_pressed);
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
};

