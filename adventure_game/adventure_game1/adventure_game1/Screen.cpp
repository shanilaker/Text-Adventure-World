#include "Screen.h"
#include "Game.h"

void Screen::draw() const {
	cls();
	gotoxy(0, 0);
	for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
		cout << screen[i] << endl;
	}
	cout << screen[Game::MAX_Y - 1];
	cout.flush();
}

void Screen::draw(int x, int y) const {
    gotoxy(x, y);
    cout << screen[y][x];
}

// The original constructor definition
Screen::Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door the_screen_door, int the_default_x, int the_default_y, Bomb the_screen_bomb): screen_bomb(the_screen_bomb),screen_riddle(the_riddle), screen_door(the_screen_door), default_y(the_default_y), default_x(the_default_x)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        screen[i] = _strdup(the_screen[i]);
    }
}

Screen::Screen(const char* the_screen[Game::MAX_Y])
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        screen[i] = _strdup(the_screen[i]);
    }
}

// **Copy Constructor** (Deep Copy)
Screen::Screen(const Screen& other):screen_riddle(other.screen_riddle), default_y(other.default_y), default_x(other.default_x), screen_door(other.screen_door), screen_bomb(other.screen_bomb)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        screen[i] = _strdup(other.screen[i]);
    }
}


Screen::~Screen()
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        if (screen[i] != nullptr) 
        {
            std::free((void*)screen[i]);
        }
    }
}

Screen& Screen::operator=(const Screen& other)
{
    if (this != &other) // Check for self-assignment
    {
        // 1. Clean up existing resources (Destructor Logic)
        for (int i = 0; i < Game::MAX_Y; i++)
        {
            if (screen[i] != nullptr) 
            {
                std::free((void*)screen[i]);
            }
        }

        // 2. Deep copy new resources
        for (int i = 0; i < Game::MAX_Y; i++)
        {
            
            if (other.screen[i] != nullptr)
            {
                screen[i] = _strdup(other.screen[i]);
            }
            else
            {
                screen[i] = nullptr;
            }
        }
        screen_riddle = other.screen_riddle;
        default_y = other.default_y;
        default_x = other.default_x;
        screen_door = other.screen_door;
        screen_bomb = other.screen_bomb;
    }
    return *this;
}

char Screen::getCharAt(int x, int y) const {
    if (x >= 0 && x < Game::MAX_X && y >= 0 && y < Game::MAX_Y) {
        return screen[y][x];
    }
    return ' '; //out of range 
}

void Screen::setCharAt(int x, int y, char ch) {
    if (x > 0 && x < Game::MAX_X - 1 && y > 0 && y < Game::MAX_Y - 1 && screen[y] != nullptr) {
        screen[y][x] = ch;
    }
}
