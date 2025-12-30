#pragma once

class Switch 
{
	int x = -1;
	int y  = -1;
	bool is_on = false;
	char on_char = '/';
	char off_char = '\\';
	bool is_active = true;
	bool is_needed = true;
public:

	//Empty ctor
	Switch() {}

	//Ctor
	Switch(int x1, int y1, bool state = false, bool needed = false) : x(x1), y(y1), is_on(state), is_needed(needed) {}

	//Get the x
	int getX() const { return x; }

	//Get the y
	int getY() const { return y; }

	//Is the switch on
	bool isOn() const { return is_on; }

	//Changes the state of the switch
	void changeState() { is_on = !is_on; }

	//Deactivates the switch
	void kill() { is_active = false; }

	//Returns whether the switch is active
	bool get_isActive() const { return is_active; }

	//Returns the shape of the switch
	char getCurrentChar() const;

	//Turns off the switch
	void set_is_on(){ is_on = false ;}

	// Returns whether switch is needed to open door
	bool isNeeded() const { return is_needed; }

	// Set whether switch is needed to open door
	void setIsNeeded(bool isneeded) { is_needed = isneeded; }
 };


