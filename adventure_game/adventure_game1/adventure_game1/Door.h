#pragma once
class Door {
	int x, y;
	char door_number = '1';
	bool is_open = false;
	int num_key_needed = 1;
public:
	Door()
	{ }
	Door(int x1, int y1, char number, int the_num_key_needed) {
		x = x1;
		y = y1;
		door_number = number;
		num_key_needed = the_num_key_needed;
	}

	int getX() const { return x; }
	int getY() const { return y; }
	bool isOpen() const { return is_open; }
	void openDoor() 
	{
		num_key_needed--;
		if (num_key_needed == 0)
		{
			is_open = true;
		}
	}
};

