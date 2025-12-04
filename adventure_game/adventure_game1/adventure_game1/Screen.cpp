#include "Screen.h"

void Screen::draw() const {
	cls();
	gotoxy(0, 0);
	for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
		cout << screen[i] << endl;
	}
	cout << screen[Game::MAX_Y - 1];
	cout.flush();
}

// The original constructor definition
Screen::Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle): screen_riddle(the_riddle)
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
Screen::Screen(const Screen& other):screen_riddle(other.screen_riddle)
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
