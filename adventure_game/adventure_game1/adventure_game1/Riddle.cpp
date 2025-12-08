#define _CRT_SECURE_NO_WARNINGS
#include "Riddle.h"

// Riddle constructor
Riddle::Riddle(const char* r_text[Game::MAX_Y], int r_x, int r_y,int r_room_connected, char the_answer): x(r_x), y(r_y), room_connected(r_room_connected), answer(the_answer)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strcpy(text[i], r_text[i]);
    }
}

// Riddle empty constructor
Riddle::Riddle() {}

// Draws riddle on screen
void Riddle::Show_Riddle() const
{
    if (is_active)
    {
        cls();
        gotoxy(0, 0);
        for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
            cout << text[i] << endl;
        }
        cout << text[Game::MAX_Y - 1];
        cout.flush();
    }
}

