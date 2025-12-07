#include "Player.h"
#include "Screens.h"

Player::Player(int x1, int y1, int diffx, int diffy, char c, const char(&the_keys)[NUM_KEYS + 1], int room_id, int riddleSolved) {
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

void Player::reset()
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

void Player::hideForTransition()
{
	x = -1;
	y = -1;
	setDirection(Direction::STAY);
}

void Player::setPosition(int x1, int y1)
{
	x = x1;
	y = y1;
	setDirection(Direction::STAY);
}

void Player::kill() {
	draw(' ');
	is_active = false;
}

void Player::draw() const {
	if (is_active)
	{
		draw(ch);
	}
}
void Player::draw(char c) const {
	if (is_active) {
		gotoxy(x, y);
		std::cout << c;
	}
}


bool Player::move(Screen& cur_screen, Game the_game) {

	int next_x = (x + diff_x + Game::MAX_X) % Game::MAX_X;
	int next_y = (y + diff_y + Game::MAX_Y) % Game::MAX_Y;

	// dispose
	if (diff_x == 99 && diff_y == 99) {
		if (hasItem()) {
			// throw item at current place
			if (getHeldItem() == '@')
			{
				cur_screen.get_bomb().set_is_activated(true);
				cur_screen.get_bomb().setX(x);
				cur_screen.get_bomb().setY(y);
				cur_screen.get_bomb().set_time_to_explode(the_game.getRuntime());
			}
			cur_screen.setCharAt(x, y, getHeldItem());
			setHeldItem('\0');
			setJustDisposed(true);
		}
		setDirection(Direction::STAY);
		return false;
	}


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
	else if (target_char == 'K' && !(diff_x == 0 && diff_y == 0)) {
		if (!hasItem() && !getJustDisposed()) {
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

		Door& door = cur_screen.getDoor();
		if (!door.getisActive())
		{
			return false;
		}
		if (door.isOpen() )
		{
			cur_screen.set_player_moved();
			if (cur_screen.get_players_moved() < 2) {
				draw(' ');
				hideForTransition();
			}
			return false;
		}
		// If door is linked to switches and they're not ON
		if (door.isLinkedToSwitches() && !cur_screen.areSwitchesCorrect()) {
			setDirection(Direction::STAY);
			return false;
		}

		// If door is linked ONLY to switches and they're correct
		if (door.isLinkedToSwitches() && door.getNumKeyNeeded() == 0)
		{
			door.openDoor();
			cur_screen.set_player_moved();
			if (cur_screen.get_players_moved() < 2)
			{
				draw(' ');
				hideForTransition();
			}
			return false;
		}

		if (door.getNumKeyNeeded() > 0 && getHeldItem() == 'K') {

			setHeldItem('\0');
			door.openDoor();

			if (door.isOpen())
			{
				cur_screen.set_player_moved();
				if (cur_screen.get_players_moved() < 2)
				{
					draw(' ');
					hideForTransition();
				}
			}
			return false;
		}

		//if you don't have the key, stay in place
		setDirection(Direction::STAY);
		return false;
	}

	else if (target_char == '@')
	{
		if (!hasItem()) {
			setHeldItem('@'); // pick up key
			cur_screen.setCharAt(next_x, next_y, ' '); // remove key from screen
			x = next_x; // go to key spot
			y = next_y;
			return false;
		}
		//if already has item - stop.
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
			setDirection(Direction::STAY);
			return false;
		}
		if (solvedRiddle == 0)
		{
			setDirection(Direction::STAY);
			solvedRiddle = -2;
			return false;
		}
		solvedRiddle = -1;
		return true;
	}

	else if (target_char == '/' || target_char == '\\')
	{
		Switch* switches = cur_screen.getSwitches();
		int num_switches = cur_screen.getNumSwitches();

		//search for the switch
		for (int i = 0; i < num_switches; ++i) {
			if (next_x == switches[i].getX() && next_y == switches[i].getY() && switches[i].get_isActive()) {
				switches[i].changeState(); // turn switch on/off

				cur_screen.setCharAt(next_x, next_y, switches[i].getCurrentChar());
				cur_screen.draw(next_x, next_y);
				break;
			}
		}
		setDirection(Direction::STAY);
		return false;
		}

	// keep moving
	else {
		if (next_x != x || next_y != y) {
			setJustDisposed(false);
		}
		cur_screen.draw(x, y);
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
	case Direction::DISPOSE:
		diff_x = 99;
		diff_y = 99;
		break;
	}
}

