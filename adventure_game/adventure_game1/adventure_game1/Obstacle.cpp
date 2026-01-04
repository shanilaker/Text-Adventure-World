#include "Obstacle.h"
#include "Screen.h"

//Draw c in x, y
void Obstacle::draw(const char& c) const {
	for (const auto& p : body) {
		gotoxy(p.getX(), p.getY());
		std::cout << c;
	}
}

//Reset the obstacle
void Obstacle::reset()
{
	body = r_body;
	force_needed = reset_force_needed;
	x = r_x;
	y = r_y;
	diff_x = 0;
	diff_y = 0;
	is_moved = false;
}

//If this is in the length of the body
bool Obstacle::occupies(int _x, int _y) const {
	for (const auto& p : body) {
		if (p.getX() == _x && p.getY() == _y)
			return true;
	}
	return false;
}

// Copied from tirgul with Amir Kirsh
void Obstacle::setDirection(Direction dir) {
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


// Reponsible for the obstacle move, calculates his next (x,y) based on speed, direction, and items that appear on its way
//void Obstacle::move(Screen& cur_screen, vector<Player>& players)
//{
//	bool cant_move = false;
//	for (auto& p : body)
//	{
//		
//
//		// Calculate the next (x,y) the player will be placed at
//		int next_x = (p.getX() + diff_x + Game::MAX_X) % Game::MAX_X;
//		int next_y = (p.getY() + diff_y + Game::MAX_Y) % Game::MAX_Y;
//
//
//		// If obstacle is about to go out of screen boundries - make it STAY in place
//		if (next_x <= 0 || next_x >= Game::MAX_X - 1 || next_y <= 0 || next_y >= Game::MAX_Y - 1) {
//			setDirection(Direction::STAY);
//		}
//
//		char target = cur_screen.getCharAt(next_x, next_y);
//		if (target == 'W' || target == 'K' || (target >= '1' && target <= '9') || (target == '*' && !in_body(next_x, next_y)) || target == '@' || target == '?' || target == '/' || target == '\\') {
//			setDirection(Direction::STAY);
//			players[0].setDirection(Direction::STAY);
//			players[1].setDirection(Direction::STAY);
//			cant_move = true;
//			
//		}
//		if (cant_move)
//		{
//			setDirection(Direction::STAY);
//			players[0].setDirection(Direction::STAY);
//			players[1].setDirection(Direction::STAY);
//		}
//
//		// keep moving
//		else if(wanted_d != Direction::STAY){
//			cur_screen.setCharAt(p.getX(), p.getY(), ' ');
//			cur_screen.draw(p.getX(), p.getY());
//			p.setX(next_x);
//			p.setY(next_y);
//			cur_screen.setCharAt(p.getX(), p.getY(), '*');
//			cur_screen.draw(p.getX(), p.getY());
//
//		}
//
//
//	}
//	players[0].set_moved_obstacle(false);
//	players[1].set_moved_obstacle(false);
//}


void Obstacle::move(Screen& cur_screen, vector<Player>& players)
{
	if (wanted_d == Direction::STAY) {
		players[0].set_moved_obstacle(false);
		players[1].set_moved_obstacle(false);
		return;
	}

	bool can_move_all = true;

	for (const auto& p : body) {
		int next_x = (p.getX() + diff_x + Game::MAX_X) % Game::MAX_X;
		int next_y = (p.getY() + diff_y + Game::MAX_Y) % Game::MAX_Y;

		if (next_x <= 0 || next_x >= Game::MAX_X - 1 || next_y <= 0 || next_y >= Game::MAX_Y - 1) {
			can_move_all = false;
			break;
		}

		char target = cur_screen.getCharAt(next_x, next_y);

		if (target != ' ' && target != '*' && target != '$' && target != '&') {
			can_move_all = false;
			break;
		}

		if (target == '*' && !in_body(next_x, next_y)) {
			can_move_all = false;
			break;
		}
	}

	if (can_move_all) {
		for (const auto& p : body) {
			cur_screen.setCharAt(p.getX(), p.getY(), ' ');
			cur_screen.draw(p.getX(), p.getY());
		}

		for (auto& p : body) {
			p.setX((p.getX() + diff_x + Game::MAX_X) % Game::MAX_X);
			p.setY((p.getY() + diff_y + Game::MAX_Y) % Game::MAX_Y);
		}

		for (const auto& p : body) {
			cur_screen.setCharAt(p.getX(), p.getY(), '*');
			cur_screen.draw(p.getX(), p.getY());
		}
	}
	else {
		setDirection(Direction::STAY);
		players[0].setDirection(Direction::STAY);
		players[1].setDirection(Direction::STAY);
	}

	players[0].set_moved_obstacle(false);
	players[1].set_moved_obstacle(false);
}

bool Obstacle::in_body(int _x, int _y)
{
	for (auto& p : body)
	{
		if (p.getX() == _x && p.getY() == _y)
		{
			return true;
		}
	}
	return false;
}


