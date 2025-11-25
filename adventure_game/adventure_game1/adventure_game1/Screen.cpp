#include "Screen.h"

void Screen::draw() const {
	cls();
	gotoxy(0, 0);
	for (size_t i = 0; i < MAX_Y - 1; ++i) {
		cout << screen[i] << endl;
	}
	cout << screen[MAX_Y - 1];
	cout.flush();
}

// The original constructor definition
Screen::Screen(const char* the_screen[MAX_Y])
{
    for (int i = 0; i < MAX_Y; i++)
    {
        screen[i] = _strdup(the_screen[i]);
    }
}

// **Copy Constructor** (Deep Copy)
Screen::Screen(const Screen& other)
{
    for (int i = 0; i < MAX_Y; i++)
    {
        screen[i] = _strdup(other.screen[i]);
    }
}


Screen::~Screen()
{
    for (int i = 0; i < MAX_Y; i++)
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
        for (int i = 0; i < MAX_Y; i++)
        {
            if (screen[i] != nullptr) 
            {
                std::free((void*)screen[i]);
            }
        }

        // 2. Deep copy new resources
        for (int i = 0; i < MAX_Y; i++)
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
    }
    return *this;
}
