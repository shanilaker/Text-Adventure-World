#pragma once

class Key 
{

private:
	int x = -1;
	int y = -1;
	char sign = 'K';
	int id = 1;
	bool is_active = true;

public:

	//Ctor
	Key(int x1, int y1, int the_id);

	//Empty ctor
	Key(){}

	//Get if the Key is active
	bool getisActive() const { return is_active; }

	//Deactivate the key
	void kill() { is_active = false; }

	//Get the x
	int getX() const { return x; }

	//Get the y
	int getY() const { return y; }

	//Get the id
	int getID() const { return id; }
};

