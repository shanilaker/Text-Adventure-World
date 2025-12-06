#pragma once
class Door {
	int x, y;
	char door_number = '1';
	bool is_open = false;
	int num_key_needed = 1;
public:
	//Empty ctor
	Door(){}

	//Ctor
	Door(int x1, int y1, char number, int the_num_key_needed):x(x1), y(y1), door_number(number),num_key_needed(the_num_key_needed) {}
	int getX() const { return x; }
	int getY() const { return y; }
	bool isOpen() const { return is_open; }

	//Updates the number of keys remaining to open the door
	void openDoor();
};

