#include "Spring.h"

bool Spring::isSpringAt(int test_x, int test_y) const {
	if ((dir == Direction::LEFT || dir == Direction::RIGHT) && test_y != y)
		return false;
	if ((dir == Direction::UP || dir == Direction::DOWN) && test_x != x)
		return false;

	for (int i = 0; i < length; i++) {
		int cur_x = x;
		int cur_y = y;

		if (dir == Direction::LEFT)
			cur_x -= i;
		else if (dir == Direction::RIGHT)
			cur_x += i;
		else if (dir == Direction::UP)
			cur_y -= i;
		else if (dir == Direction::DOWN)
			cur_y += i;

		if (test_x == cur_x && test_y == cur_y) {
			return true;
		}
	}
	return false;
}

//Load the Spring state
void Spring::load(std::istream& in) {
	int dir_int;
	in >> x >> y >> length >> dir_int;
	dir = (Direction)dir_int;
}