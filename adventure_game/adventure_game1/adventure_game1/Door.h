#pragma once
class Door {
	int x, y;
	char door_number = '1';
	bool is_open = false;
	int matching_key = 1;
public:
	Door(int x1, int y1, char number) {
		x = x1;
		y = y1;
		door_number = number;
	}

	int getX() const { return x; }
	int getY() const { return y; }
	bool isOpen() const { return is_open; }
	void openDoor() { is_open = true; }
};

