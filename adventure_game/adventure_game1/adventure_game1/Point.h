#pragma once
class Point
{
	int x = -1;
	int y = -1;
	int data = 0;

public:

	//Ctor
	Point(int _x, int _y, int _data = 0):x(_x), y(_y), data(_data){}

	//Ctor
	Point(int _data) :data(_data) {}

	//Empty ctor
	Point(){}

	//Get x
	int getX() const { return x; }

	//Get y
	int getY() const { return y; }

	//Set data
	void setData(int value) { data = value; }

	//Get data
	int getData() { return data; }

	//Set x
	void setX(int _x) { x = _x; }

	//Set y
	void setY(int _y) { y = _y; }
};

