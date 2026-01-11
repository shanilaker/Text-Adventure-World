#pragma once
#include <iostream>

class Door 
{
	int x = -1;
	int y = -1;
	char door_number = '1';
	bool is_open = false;
	int num_key_needed = 1;
	int reset_num_key_needed = 1;
	bool is_active = true;
	bool linked_to_switches = false;
	int target_room_index = -1;
public:
	//Empty ctor
	Door(){}

	//Ctor
	Door(int x1, int y1, char number, int the_num_key_needed, bool linked_switches) :x(x1), y(y1), door_number(number), num_key_needed(the_num_key_needed), reset_num_key_needed(the_num_key_needed), linked_to_switches(linked_switches){}

	//Get x
	int getX() const { return x; }

	//Get y
	int getY() const { return y; }

	//Return if the door is open
	bool isOpen() const { return is_open; }

	//Get if the door is active
	bool getisActive() const { return is_active; }

	//Deactivate the door
	void kill() { is_active = false; }

	//Updates the number of keys remaining to open the door and open the door accordingly
	void openDoor();

	//Close the door
	void set_is_open(){ is_open = false; }

	//Dactivate the door
	void setisActive(){ is_active = true; }

	//Reset the number of keys needed to open the door
	void resetNumKeyNeeded(){ num_key_needed = reset_num_key_needed; }

	// Set the number of keys needed to open the door
	void setNumKeyNeeded(int num_needed);

	// Set the number of keys needed to open the door
	void setResetNumKeyNeeded(int num_needed) { reset_num_key_needed = num_needed; }

	//Returns if the door link to switches
	bool isLinkedToSwitches() const { return linked_to_switches; }

	//Get the number of key needed
	int getNumKeyNeeded() const { return num_key_needed; }

	// set if linked to switches
	void setLinkedToSwitches(bool islinked) { linked_to_switches = islinked; }

	// Set the target room
	void setTargetRoom(int index) { target_room_index = index; }

	// Get the target room
	int getTargetRoom() const { return target_room_index; }

	// Get the door char
	char getChar() const { return door_number; }

	//Saves the door state
	void save(std::ostream& out) const {out << x << " " << y << " " << is_open << " " << is_active << " " << num_key_needed << " " << linked_to_switches << std::endl;}

	//Load the door state
	void load(std::istream& in) {in >> x >> y >> is_open >> is_active >> num_key_needed >> linked_to_switches;}

};

