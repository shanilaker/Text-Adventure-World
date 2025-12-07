#pragma once
class Key {

private:
	int x, y;
	char sign = 'K';
	int id = 1;
	bool is_active = true;
public:
	Key(int x1, int y1, int the_id)
	{
		x = x1;
		y = y1;
		id = the_id;
	}
	Key(){}
	bool getisActive() const { return is_active; }
	void kill() { is_active = false; }
	int getX() const { return x; }
	int getY() const { return y; }
	int getID() const { return id; }
};

