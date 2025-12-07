#pragma once
class Door {
	int x, y;
	char door_number = '1';
	bool is_open = false;
	int num_key_needed = 1;
	int reset_num_key_needed = 1;
	bool is_active = true;
	bool linked_to_switches = false;

public:
	//Empty ctor
	Door(){}

	//Ctor

	Door(int x1, int y1, char number, int the_num_key_needed, bool linked_switches) :x(x1), y(y1), door_number(number), num_key_needed(the_num_key_needed), linked_to_switches(linked_switches), reset_num_key_needed(the_num_key_needed){}

	int getX() const { return x; }
	int getY() const { return y; }
	bool isOpen() const { return is_open; }
	bool getisActive() const { return is_active; }
	void kill() { is_active = false; }
	//Updates the number of keys remaining to open the door
	void openDoor();
	void set_is_open()
	{
		is_open = false;
	}
	void setisActive(bool value)
	{
		is_active = true;
	}
	void set_num_key_needed()
	{
		num_key_needed = reset_num_key_needed;
	}
	bool isLinkedToSwitches() const { return linked_to_switches; }
	int getNumKeyNeeded() const { return num_key_needed; }
};

