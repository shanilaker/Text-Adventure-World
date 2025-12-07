#pragma once

class Switch {
	int x, y;
	bool is_on = false;
	char on_char = '/';
	char off_char = '\\';
	bool is_active = true;
public:
	Switch() {}
	Switch(int x1, int y1, bool state = false) : x(x1), y(y1), is_on(state) {}

	int getX() const { return x; }
	int getY() const { return y; }

	bool isOn() const { return is_on; }
	void changeState() { is_on = !is_on; }
	void kill() { is_active = false; }
	bool get_isActive()
	{
		return is_active;
	}
	char getCurrentChar() const {
		if (is_on) {
			return on_char;
		}
		return off_char;
	}
	void set_is_on()
	{
		is_on = false;
	}
};


