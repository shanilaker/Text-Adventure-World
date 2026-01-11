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

		if (target != Object::SPACE && target != Object::OBSTACLE && target != '$' && target != '&') {
			can_move_all = false;
			break;
		}

		if (target == Object::OBSTACLE && !in_body(next_x, next_y)) {
			can_move_all = false;
			break;
		}
	}

	if (can_move_all) {
		for (const auto& p : body) {
			cur_screen.setCharAt(p.getX(), p.getY(), Object::SPACE);
			cur_screen.draw(p.getX(), p.getY());
		}

		for (auto& p : body) {
			p.setX((p.getX() + diff_x + Game::MAX_X) % Game::MAX_X);
			p.setY((p.getY() + diff_y + Game::MAX_Y) % Game::MAX_Y);
		}

		for (const auto& p : body) {
			cur_screen.setCharAt(p.getX(), p.getY(), Object::OBSTACLE);
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

//Save the Obstacle state
void Obstacle::save(std::ostream& out) const {
	out << x << " " << y << " " << diff_x << " " << diff_y << " "
		<< force_needed << " " << is_moved << " " << (int)wanted_d << " ";

	out << body.size() << " ";
	for (const auto& p : body) {
		out << p.getX() << " " << p.getY() << " ";
	}
	out << std::endl;
}

//Load the Obstacle state
void Obstacle::load(std::istream& in) {
	int dir_int;
	size_t body_size;
	in >> x >> y >> diff_x >> diff_y >> force_needed >> is_moved >> dir_int >> body_size;
	wanted_d = (Direction)dir_int;

	body.resize(body_size);
	for (size_t i = 0; i < body_size; ++i) {
		int px, py;
		in >> px >> py;
		body[i] = Point(px, py);
	}
}
