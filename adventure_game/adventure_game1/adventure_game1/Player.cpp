#include "Player.h"
#include "Screens.h"


bool Player::move(Screen& cur_screen) {

	// dispose
	if (diff_x == 99 || diff_y == 99) {
		if (hasItem()) {
			// throw item at current place
			cur_screen.setCharAt(x, y, getHeldItem());
			setHeldItem('\0');
		}
		setDirection(Direction::STAY);
		return false;
	}

	int next_x = (x + diff_x + Game::MAX_X) % Game::MAX_X;
	int next_y = (y + diff_y + Game::MAX_Y) % Game::MAX_Y;

	// check boundries
	if (next_x <= 0 || next_x >= Game::MAX_X - 1 || next_y <= 0 || next_y >= Game::MAX_Y - 1) {
		setDirection(Direction::STAY);
		return false;
	}

	char target_char = cur_screen.getCharAt(next_x, next_y);

	// check wall
	if (target_char == 'W' || target_char == '|' || target_char == '-') {
		setDirection(Direction::STAY);
		return false;
	}

	// check key
	else if (target_char == 'K') {
		if (!hasItem()) {
			setHeldItem('K'); // pick up key
			cur_screen.setCharAt(next_x, next_y, ' '); // remove key from screen
			x = next_x; // go to key spot
			y = next_y;
			return false;
		}
		//if already has item - stop.
		setDirection(Direction::STAY);
		return false;
	}

	// check if target is door
	else if (target_char >= '1' && target_char <= '9') {
		// DOOR 1 OPENS WITH K
		if (target_char == '1' && getHeldItem() == 'K') {
			setHeldItem('\0'); //remove key after using it
			cur_screen.setCharAt(next_x, next_y, ' '); // //open door - set as key

			x = next_x; //go into the door
			y = next_y;
			return false;
		}

		// //if you don't have the key, stay in place
		setDirection(Direction::STAY);
		return false;
	}

	
	else if (target_char == '?')
	{
		if (solvedRiddle == 1)
		{
			cur_screen.setCharAt(next_x, next_y, ' ');
			x = next_x;
			y = next_y;
			solvedRiddle = 0;
			return false;
		}
		if (solvedRiddle = 0)
		{
			return false;
		}
		solvedRiddle = -1;
		return true;
	}

	// keep moving
	else {
		x = next_x;
		y = next_y;
		return false;
	}
}



void Player::handleKeyPressed(char key_pressed) {
	size_t index = 0;
	for (char k : keys) {
		if (std::tolower(k) == std::tolower(key_pressed)) {
			setDirection((Direction)index);
			return;
		}
		++index;
	}
}

void Player::setDirection(Direction dir) {
	switch (dir) {
	case Direction::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case Direction::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case Direction::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case Direction::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case Direction::STAY:
		diff_x = 0;
		diff_y = 0;
		break;
	}
}

