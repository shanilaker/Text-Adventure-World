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
void Screen::reset(vector<Player>& players)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            screen[i][j] = screen_reset[i][j];
        }
    }
    
    screen_legend.draw(screen, players);
    screen_legend.draw(screen_reset, players);
    for (int i = 0; i < riddles.size();i++)
    {
        riddles[i].reset();
    }

    screen_door.setisActive();
    for (int i = 0; i < bombs.size();i++)
    {
        bombs[i].reset();
    }
    for (int i = 0; i < obstacles.size();i++)
    {
        obstacles[i].reset();
    }
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
    // Checks if all switches needed in the room are ON and rest are off
    for (int i = 0; i < num_switches; i++) {
        if (screen_switches[i].isOn()) {
            if (!screen_switches[i].isNeeded())
                return false;
        }
        else {
            if (screen_switches[i].isNeeded())
                return false;
        }
    }
    return true;
}

// Constructor 
Screen::Screen(const char* the_screen[Game::MAX_Y],Door the_screen_door, int the_default_x, int the_default_y, const Switch the_switches[], int count, Legend _screen_legend, vector<Bomb>& _bombs, vector<Obstacle>& _obstacles, vector<Riddle>& _riddles, const Spring the_springs[], int spring_count)
    :screen_door(the_screen_door), default_y(the_default_y), default_x(the_default_x), num_switches(count), screen_legend(_screen_legend),bombs(_bombs), obstacles(_obstacles), riddles(_riddles), num_springs(spring_count)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strncpy_s(screen[i], the_screen[i], Game::MAX_X);
        strncpy_s(screen_reset[i], the_screen[i], Game::MAX_X);
    }
    for (int i = 0; i < count && i < MAX_SWITCHES; i++) {
        screen_switches[i] = the_switches[i];
    }
    for (int i = 0; i < spring_count && i < MAX_SPRINGS; i++) {
        screen_springs[i] = the_springs[i];
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

Spring* Screen::getSpringAt(int x, int y) {
    for (int i = 0; i < num_springs; i++) {
        // if found the spring in (x,y) - return it
        if (screen_springs[i].isSpringAt(x, y)) {
            return &screen_springs[i];
        }
    }
    return nullptr;
}

void Screen::restoreSprings() {
    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) {
            // If original screen had a spring and it's gone - put it back
            if (screen_reset[i][j] == '#' && screen[i][j] == ' ') {
                screen[i][j] = '#';
                draw(j, i);
            }
        }
    }
}


void Screen::drawDark(vector<Player>& players) const {
    int radius = 6;

    for (int i = 0; i < Game::MAX_Y; i++) {
        std::string line = "";

        for (int j = 0; j < Game::MAX_X; j++) {
            char current_map_char = screen[i][j];
            char char_to_draw = ' ';

            bool in_light = false;
            bool is_border = (i == 0 || i == Game::MAX_Y - 1 || j == 0 || j == Game::MAX_X - 1);
            bool is_torch = (current_map_char == '!');

            for (int p = 0; p < 2; p++) {
                if (players[p].getIsActive()) {
                    int r = (players[p].getHeldItem() == '!') ? radius : 0;
                    if (std::abs(players[p].getX() - j) <= r && std::abs(players[p].getY() - i) <= r) {
                        in_light = true;
                        break;
                    }
                }
            }

            if (in_light || is_border || is_torch) {
                char_to_draw = current_map_char;

                if (in_light) {
                    for (int p = 0; p < 2; p++) {
                        if (players[p].isActive() && !players[p].isWaiting() && players[p].getX() == j && players[p].getY() == i) {
                            char_to_draw = players[p].get_char();
                        }
                    }
                }
            }
            line += char_to_draw;
        }

        gotoxy(0, i);
        std::cout << line;
    }
    std::cout.flush();
}

