#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Screen.h"



void Screen::draw(int x, int y) const {
    gotoxy(x, y);
    cout << screen[y][x];
}

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
Screen::Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door the_screen_door, int the_default_x, int the_default_y, Bomb the_screen_bomb, const Switch the_switches[], int count, int required_on)
    : screen_bomb(the_screen_bomb), screen_riddle(the_riddle), screen_door(the_screen_door), default_y(the_default_y), default_x(the_default_x), num_switches(count), required_on_switches(required_on)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strcpy(screen[i], the_screen[i]);
        strcpy(screen_reset[i], the_screen[i]);
    }
    for (int i = 0; i < count && i < MAX_SWITCHES; i++) {
        screen_switches[i] = the_switches[i];
    }
}

Screen::Screen(const char* the_screen[Game::MAX_Y])
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strcpy(screen[i], the_screen[i]);
        strcpy(screen_reset[i], the_screen[i]);
    }
}

//// **Copy Constructor** (Deep Copy)
//Screen::Screen(const Screen& other) :screen_riddle(other.screen_riddle), default_y(other.default_y), default_x(other.default_x), screen_door(other.screen_door), screen_bomb(other.screen_bomb), num_switches(other.num_switches), required_on_switches(other.required_on_switches)
//{
//    for (int i = 0; i < Game::MAX_Y; i++)
//    {
//        strcpy(screen[i], other.screen[i]);
//        strcpy(screen_reset[i], other.screen[i]);
//    }
//    for (int i = 0; i < other.num_switches; i++) {
//        screen_switches[i] = other.screen_switches[i];
//    }
//}


//Screen::~Screen()
//{
//
//}

//Screen& Screen::operator=(const Screen& other)
//{
//    if (this != &other) // Check for self-assignment
//    {
//        for (int i = 0; i < Game::MAX_Y; i++)
//        {
//
//            strcpy(screen[i], other.screen[i]);
//            strcpy(screen_reset[i], other.screen[i]);
//
//        }
//        screen_riddle = other.screen_riddle;
//        default_y = other.default_y;
//        default_x = other.default_x;
//        screen_door = other.screen_door;
//        screen_bomb = other.screen_bomb;
//        num_switches = other.num_switches;
//        required_on_switches = other.required_on_switches;
//        for (int i = 0; i < other.num_switches; ++i) {
//            screen_switches[i] = other.screen_switches[i];
//        }
//
//    }
//    return *this;
//}

char Screen::getCharAt(int x, int y) const {
    if (x >= 0 && x < Game::MAX_X && y >= 0 && y < Game::MAX_Y) {
        return screen[y][x];
    }
    return ' '; //out of range 
}

void Screen::setCharAt(int x, int y, char ch) {
    if (x >= 0 && x <= Game::MAX_X - 1 && y >= 0 && y <= Game::MAX_Y - 1 && screen[y] != nullptr) {
        screen[y][x] = ch;
    }
}

