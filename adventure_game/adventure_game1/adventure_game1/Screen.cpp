#include "Game.h"
#include "Screen.h"

// Empty constructor
Screen::Screen()
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            screen[i][j] = ' ';
            screen_reset[i][j] = ' ';
        }
    }
}

// Resets screen for next gane
void Screen::reset()
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            screen[i][j] = screen_reset[i][j];
        }
    }
    screen_riddle.setisActive(true);
    screen_door.setisActive();
    screen_bomb.setisActive(true);
    screen_bomb.set_is_activated(false, -1,-1);
    screen_bomb.set_time_to_explode(-6);
    players_moved = 0;
    for (int i = 0;i < num_switches;i++)
    {
        screen_switches[i].set_is_on();
    }
    screen_door.set_num_key_needed();
    screen_door.set_is_open();
}

// Draws a specific (x,y) on the screen
void Screen::draw(const int & x, const int& y) const {
    gotoxy(x, y);
    cout << screen[y][x];
}

// Draws screen
void Screen::draw() const {
    cls();
    gotoxy(0, 0);
    for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
        cout << screen[i] << endl;
    }
    cout << screen[Game::MAX_Y - 1];
    cout.flush();
}


bool Screen::areSwitchesCorrect() const {
    int count = 0;
    // Checks if all switches in the room are ON
    for (int i = 0; i < num_switches; i++) {
        if (screen_switches[i].isOn()) {
            count++;
        }
    }
    return count == required_on_switches;
}

// Constructor 
Screen::Screen(const char* the_screen[Game::MAX_Y], Riddle the_riddle, Door the_screen_door, int the_default_x, int the_default_y, Bomb the_screen_bomb, const Switch the_switches[], int count, int required_on)
    : screen_bomb(the_screen_bomb), screen_riddle(the_riddle), screen_door(the_screen_door), default_y(the_default_y), default_x(the_default_x), num_switches(count), required_on_switches(required_on)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strncpy_s(screen[i], the_screen[i], Game::MAX_X);
        strncpy_s(screen_reset[i], the_screen[i], Game::MAX_X);
    }
    for (int i = 0; i < count && i < MAX_SWITCHES; i++) {
        screen_switches[i] = the_switches[i];
    }
}

Screen::Screen(const char* the_screen[Game::MAX_Y])
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strncpy_s(screen[i], the_screen[i], Game::MAX_X);
        strncpy_s(screen_reset[i], the_screen[i], Game::MAX_X);
    }
}

char Screen::getCharAt(const int& x, const int& y) const {
    // checks if (x,y) is in screen boundries
    if (x >= 0 && x < Game::MAX_X && y >= 0 && y < Game::MAX_Y) {
        return screen[y][x];
    }
    return ' '; //out of range 
}

void Screen::setCharAt(const int& x, const int& y, const char & ch) {
    // checks if (x,y) is in screen boundries
    if (x >= 0 && x <= Game::MAX_X - 1 && y >= 0 && y <= Game::MAX_Y - 1 && screen[y] != nullptr) {
        screen[y][x] = ch;
    }
}

