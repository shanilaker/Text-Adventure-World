#include "Player.h"
#include "Screens.h"


vector<Player> Player::players;

//Player constructor
Player::Player(int x1, int y1, int diffx, int diffy, char c, const char(&the_keys)[NUM_KEYS + 1], int room_id, int riddleSolved) :x(x1), y(y1), diff_x(diffx), diff_y(diffy),ch(c), current_room_id(room_id),reset_valueX(x1),reset_valueY(y1),diff_valueX(diffx),diff_valueY(diffy),life(Point(3)),score(Point(0))
{
	memcpy(keys, the_keys, NUM_KEYS * sizeof(keys[0]));
	riddleSolved = solvedRiddle;
}

void Player::setHeldItem(char item, Screen& cur_screen)
{ 
	held_item = item;

	for (auto& p : players) {
		if (p.ch == this->ch) {
			p.held_item = item;
			break;
		}
	}

	cur_screen.get_screen_legend().update_values(ch, players,cur_screen);
}

void Player::checkAndkill(int bomb_x, int bomb_y, int& game_state)
{
	//GEMINI HELPED
			//Player distance from bomb
	int dist_x = std::abs(x - bomb_x);
	int dist_y = std::abs(y - bomb_y);

	int max_dist = max(dist_x, dist_y);

	//Eliminates a player if they are still alive and within 3 yards in any direction.
	if (max_dist <= 3 && is_active)
	{
		life.downingData();
		if (life.getData() == 0)
		{
			kill();
			game_state = LOSE;
		}
	}
}

// Resets player values for next game
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
	life.setData(3);
	score.setData(0);
}

// When player went into the next level and waiting for other player - places it in temporary coord where it is hidden
void Player::hideForTransition()
{
	x = -1;
	y = -1;
	setDirection(Direction::STAY);
}

// Places player on a (x,y) on the screen
void Player::setPosition(const Point& start)
{
	x = start.getX();
	y = start.getY();
	setDirection(Direction::STAY);
}

// When player explodes from bomb, hides it from screen and marks it as Inactive
void Player::kill() {
	draw(' ');
	is_active = false;
}

// Draws player on the screen
void Player::draw() const {
	if (is_active)
	{
		draw(ch);
	}
}

// Draw player on the screen with the given char as symbol
void Player::draw(const char & c) const {
	if (is_active) {
		gotoxy(x, y);
		std::cout << c;
	}
}

// Reponsible for the player move, calculates his next (x,y) based on speed, direction, and items that appear on its way
bool Player::move(Screen& cur_screen, Game the_game,Player& other_player)
{
	int cur_speed = (boost_time > 0) ? boost_speed : 1;

	// Calculate the next (x,y) the player will be placed at
	int next_x = x;
	int next_y = y;

	bool hit_obstacle = false;

	for (int step = 0; step < cur_speed; ++step) {
		int temp_x = (next_x + diff_x + Game::MAX_X) % Game::MAX_X;
		int temp_y = (next_y + diff_y + Game::MAX_Y) % Game::MAX_Y;

		// Transfer boost to other player if collided
		if (other_player.isActive() && temp_x == other_player.getX() && temp_y == other_player.getY()) {
			if (boost_time > 0) {
				other_player.setBoost(boost_speed, boost_time, boost_dir);
			}
		}

		char step_char = cur_screen.getCharAt(temp_x, temp_y);

		if (step_char == '*') {
			move_to_obstacle(cur_screen, players, temp_x, temp_y);
		}

		if (step_char == 'W') {
			hit_obstacle = true;
			break;
		}
		next_x = temp_x;
		next_y = temp_y;
	}

	if (boost_time > 0) {
		boost_time--;
		if (boost_time == 0 || hit_obstacle) {
			boost_speed = 1;
			boost_time = 0;
			boost_dir = Direction::STAY;
		}
	}

	bool direction_changed = false;
	if (boost_count > 0 && (diff_x != 0 || diff_y != 0)) {
		Spring* s = cur_screen.getSpringAt(x, y);
		if (s && p_dir != getOppositeDirection(s->getDir())) {
			direction_changed = true;
		}
	}


	for (auto& obstacle : cur_screen.get_obstacles())
	{
		if (obstacle.get_is_moved() == true)
		{
			obstacle.set_is_moved(false);
		}
	}
	char target_char = cur_screen.getCharAt(next_x, next_y); // gets the char the player is about to hit

	// If player pressed DISPOSE (marked as diff_x & diff_y == 9)
	if (diff_x == 99 && diff_y == 99) {
		if (hasItem()) {
			// if player is throwing a bomb 
			if (getHeldItem() == '@' && (target_char != '|' && target_char != '-'))
			{
				for (auto& bomb : cur_screen.get_bombs())
				{
					if (bomb.getX() == -2 && bomb.getY() == -2)
					{
						bomb.setX(x);
						bomb.setY(y);
						bomb.set_is_activated(true, x, y);
						bomb.set_time_to_explode(the_game.getRuntime());
						break;
					}
					
				}
			}
			cur_screen.setCharAt(x, y, getHeldItem()); // throw held item at current place
			setHeldItem('\0', cur_screen); // set held item to nothing and update legend
			setJustDisposed(true);
		}
		setDirection(Direction::STAY);
		return false;
	}


	// If player is about to go out of screen boundries - make it STAY in place
	if (next_x <= 0 || next_x >= Game::MAX_X - 1 || next_y <= 0 || next_y >= Game::MAX_Y - 1) {
		setDirection(Direction::STAY);
		return false;
	}

	// If target is spring
	if (target_char == '#') {
		return move_to_spring(next_x, next_y, cur_screen);
	}

	if (boost_count > 0 && (hit_obstacle || direction_changed || (diff_x == 0 && diff_y == 0))) {
		Spring* spring = cur_screen.getSpringAt(x, y);
		if (spring) {
			boost_speed = boost_count;
			boost_time = (boost_count * boost_count);
			boost_dir = spring->getDir();
			setDirection(boost_dir);
			cur_screen.restoreSprings();
		}
		boost_count = 0;
		return false;
	}

	// if target is Wall, stay in place
	else if (target_char == 'W') {
		setDirection(Direction::STAY);
		return false;
	}

	// if target is Torch
	else if (target_char == '!' && !(diff_x == 0 && diff_y == 0)) {
		if (!hasItem()) {
			setHeldItem('!', cur_screen);
			cur_screen.setCharAt(next_x, next_y, ' ');
			x = next_x;
			y = next_y;
			return false;
		}
		setDirection(Direction::STAY);
		return false;
	}

	// if target is Wall, stay in place
	if (target_char == '|' || target_char == '-') {
		setDirection(Direction::STAY);
		return false;
	}

	// if Target is Key 
	else if (target_char == 'K' && !(diff_x == 0 && diff_y == 0)) {

		return take_key(cur_screen, next_x, next_y);
	}

	// If target is door
	else if (target_char >= '1' && target_char <= '9') {

		Door& door = cur_screen.getDoor(target_char);
		return move_to_door(door, cur_screen);
	}

	// If target is obstacle
	else if (target_char == '*')
	{
		for (auto& obstacle : cur_screen.get_obstacles())
		{

			if (obstacle.occupies(next_x, next_y))
			{
				return move_to_obstacle(cur_screen, players, next_x, next_y);
			}
			
		}
		return false;
	}

	// If target is bomb
	else if (target_char == '@' && !(diff_x == 0 && diff_y == 0))
	{
		return move_to_bomb(next_x, next_y, cur_screen);
	}

	// If target is riddle
	else if (target_char == '?')
	{
		return move_to_riddle(next_x, next_y, cur_screen);
	}

	// If target is switch
	else if (target_char == '/' || target_char == '\\')
	{
		return move_to_switch(next_x, next_y, cur_screen);
	}

		// keep moving
	else {
			if (next_x != x || next_y != y) 
			{
				setJustDisposed(false);
			}
			cur_screen.draw(x, y);
			x = next_x;
			y = next_y;
			return false;
		}
}

bool Player::move_to_switch(const int& next_x, const int& next_y, Screen& cur_screen)
{
	auto& switches = cur_screen.getSwitches();
	size_t num_switches = cur_screen.getNumSwitches();

	// search for the switch of the current room
	for (int i = 0; i < num_switches; ++i) {
		if (next_x == switches[i].getX() && next_y == switches[i].getY() && switches[i].get_isActive()) { //if found switch
			switches[i].changeState(); // turn switch on/off

			cur_screen.setCharAt(next_x, next_y, switches[i].getCurrentChar()); //change to new state char on screen
			cur_screen.draw(next_x, next_y);
			break;
		}
	}
	setDirection(Direction::STAY);
	return false;
}

// Copied from tirgul with Amir Kirsh 
void Player::handleKeyPressed(const char & key_pressed) {
	size_t index = 0;
	for (char k : keys) {
		if (std::tolower(k) == std::tolower(key_pressed)) {
			setDirection((Direction)index);
			return;
		}
		++index;
	}
}


bool Player::move_to_riddle(const int& next_x, const int & next_y, Screen& cur_screen)
{
	
	// if answer is correct
	if (getsolvedRiddle() == 1)
	{
		cur_screen.setCharAt(next_x, next_y, ' ');
		x = next_x;
		y = next_y;
		setsolvedRiddle(-2);
		setDirection(Direction::STAY);
		return false;
	}
	// if answer is NOT correct
	if (getsolvedRiddle() == 0)
	{
		setDirection(Direction::STAY);
		setsolvedRiddle(-2);
		return false;
	}

	for (auto& riddle : cur_screen.get_riddles()) {
		if (riddle.getX() == next_x && riddle.getY() == next_y && riddle.getisActive()) {
			riddle.setActivated(true); 
			setsolvedRiddle(-1); 
			return true;
		}
	}
	return false;
}
//Associate with a door
bool Player::move_to_door(Door& door, Screen& cur_screen)
{
	if (!door.getisActive())
		return false;

	if (door.getNumKeyNeeded() > 0 && getHeldItem() == 'K') {
		door.openDoor();
		setHeldItem('\0', cur_screen);
	}

	bool switches_ok = !door.isLinkedToSwitches() || cur_screen.areSwitchesCorrect(door.getChar());

	if ((door.isOpen() || door.getNumKeyNeeded() == 0) && switches_ok)
	{
		this->current_room_id = door.getTargetRoom();
		cur_screen.set_player_moved();

		if (cur_screen.get_players_moved() < 2) {
			draw(' ');
			hideForTransition();
		}
		return false;
	}
	//if you don't have the key, stay in place
	setDirection(Direction::STAY);
	return false;
}

//If moved to obstacle
bool Player::move_to_obstacle(Screen& cur_screen, vector<Player>& _players,int _x,int _y)
{

	for (auto& obstacle : cur_screen.get_obstacles())
	{
		if (obstacle.occupies(_x, _y))
		{
			//The first touch in the obstacle rest the params
			if (!moved_obstacle)
			{
				obstacle.set_force_needed(boost_speed);
				moved_obstacle = true;
				obstacle.set_wanted_d(p_dir);
			}

			//If we need to move the Obstacle: someone already toach + the needed force + the right direction 
			if (obstacle.get_force_needed() <= 0 && moved_obstacle && obstacle.get_wanted_d() == p_dir)
			{
				obstacle.set_diff_x(diff_x);
				obstacle.set_diff_y(diff_y);
				obstacle.move(cur_screen, _players);
				obstacle.set_is_moved(true);
			}

			//If it is not enough to move the obstacle
			else if (!moved_obstacle)
			{
				setDirection(Direction::STAY);
			}
			
		}
		
	}
	return false;
}


bool Player::move_to_bomb(const int& next_x, const int& next_y, Screen& cur_screen)
{
	if (!hasItem()) {
		setHeldItem('@', cur_screen); // pick up bomb and update legend
		for (auto& bomb : cur_screen.get_bombs())
		{
			if (bomb.getX() == next_x && bomb.getY() == next_y)
			{
				bomb.setX(-2);
				bomb.setY(-2);
				break;
			}
		}
		
		cur_screen.setCharAt(next_x, next_y, ' '); // remove bomb from screen
		x = next_x; // go to bomb spot
		y = next_y;
		return false;
	}
	//if already has item - stop.
	setDirection(Direction::STAY);
	return false;
}


bool Player::move_to_spring(const int& next_x, const int& next_y, Screen& cur_screen)
{
	Spring* spring = cur_screen.getSpringAt(next_x, next_y);
	if (spring && p_dir == getOppositeDirection(spring->getDir())) {
		if (boost_count < spring->getLength()) {
			boost_count++;
			cur_screen.setCharAt(next_x, next_y, ' ');
			cur_screen.draw(next_x, next_y);
		}
		x = next_x;
		y = next_y;
		return false;
	}
	setDirection(Direction::STAY);
	return false;
}

void Player::setBoost(int speed, int time, Direction dir) {
	boost_speed = speed;
	boost_time = time;
	boost_dir = dir;
	setDirection(dir);
}

//Take the key if can
bool Player::take_key(Screen& cur_screen, const int& next_x, const int& next_y)
{
	if (!hasItem() && !getJustDisposed()) { // if doesn't have held item
		setHeldItem('K', cur_screen); // pick up key and update legend
		cur_screen.setCharAt(next_x, next_y, ' '); // remove key from screen
		x = next_x; // go to key spot
		y = next_y;
		return false;
	}
	//if already has item - stop.
	setDirection(Direction::STAY);
	return false;
}

// Copied from tirgul with Amir Kirsh
void Player::setDirection(Direction dir) {
	if (boost_time > 0) {
		if (dir == Direction::STAY || dir == getOppositeDirection(boost_dir)) {
			return;
		}
		boost_dir = dir;
	}
	if (dir != Direction::STAY && dir != Direction::DISPOSE) {
		p_dir = dir;
	}
	//p_dir = dir;
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
	case Direction::DISPOSE: // diff_x & diff_y = 99 marked as DISPOSE
		diff_x = 99;
		diff_y = 99;
		break;
	}
}


Direction Player::getOppositeDirection(Direction dir) {
	switch (dir) {
	case Direction::UP:
		return Direction::DOWN;
	case Direction::DOWN:
		return Direction::UP;
	case Direction::LEFT:
		return Direction::RIGHT;
	case Direction::RIGHT:
		return Direction::LEFT;
	default:
		return Direction::STAY;
	}
}