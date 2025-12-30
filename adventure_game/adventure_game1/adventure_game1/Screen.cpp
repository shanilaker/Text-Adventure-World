#include "Game.h"
#include "Screen.h"
#include<fstream>
#include <iostream>
#include <string>


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
    screen_door.resetNumKeyNeeded();
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

//From tirgul with amir
//void Screen::load(const std::string& filename) 
//{
//    Point l_p;
//    std::ifstream screen_file(filename);
//    // std::cout << screen_file.is_open() << std::endl;
//    // TODO: handle errors (all sort of...) - do not submit it like that :)
//    int curr_row = 0;
//    int curr_col = 0;
//    char c;
//    while (!screen_file.get(c).eof() && curr_row < Game::MAX_Y) {
//        if (c == '\n') {
//            if (curr_col < Game::MAX_X) {
//                // add spaces for missing cols
//                #pragma warning(suppress : 4996) // to allow strcpy
//                strcpy(screen[curr_row] + curr_col, std::string(Game::MAX_X - curr_col - 1, ' ').c_str());
//            }
//            ++curr_row;
//            curr_col = 0;
//            continue;
//        }
//        if (curr_col < Game::MAX_X) {
//            // handle special chars
//            if (c == '@')
//            {
//                bombs.push_back(Bomb(false, curr_col, curr_row, -1));
//            }
//            else if (c == '\\') 
//            {
//                screen_switches[num_switches] = Switch(curr_col, curr_row,false,false);
//                num_switches++;
//            }
//            else if (c == 'L') 
//            {
//                l_p.setX(curr_col); 
//                l_p.setY(curr_row);
//                screen[curr_row][curr_col] = ' ';
//            }
//            else if (c >= '1' && c <= '9')
//            {
//                screen_door = Door(curr_col, curr_row,c,1,false);
//            }
//
//            /*else if (c == '*')
//            {
//
//            }
//
//            else if (c == '#')
//            {
//
//            }*/
//
//            screen[curr_row][curr_col++] = c;
//        }
//    }
//
//
//    int last_row = (curr_row < Game::MAX_Y ? curr_row : Game::MAX_Y - 1);
//
//    // add a closing frame
//    // first line
//    #pragma warning(suppress : 4996) // to allow strcpy
//    strcpy(screen[0], std::string(Game::MAX_X, 'W').c_str());
//    screen[0][Game::MAX_X] = '\n';
//
//    // last line
//    #pragma warning(suppress : 4996) // to allow strcpy
//    strcpy(screen[last_row], std::string(Game::MAX_X, 'W').c_str());
//    screen[last_row][Game::MAX_X] = '\0';
//
//    // first col + last col
//    for (int row = 1; row < last_row; ++row) {
//        screen[row][0] = 'W';
//        screen[row][Game::MAX_X - 1] = 'W';
//        screen[row][Game::MAX_X] = '\n';
//    }
//
//    screen_legend = Legend(l_p,screen);
//}


void Screen::load(const std::string& filename, int index)
{
    Point l_p;
    std::string firstPart;
    std::string secondPart;
    std::ifstream screen_file(filename);
    if (!screen_file.is_open()) return;

    int curr_row = 0;
    int curr_col = 0;
    char c;
    std::string str;

    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) screen[i][j] = ' ';
        screen[i][Game::MAX_X] = '\0'; 
    }
    
    while (screen_file.get(c) && curr_row < Game::MAX_Y) {
        if (c == '\r') continue; 
        if (c == '\n') {
            curr_row++;
            curr_col = 0;
            continue;
        }

        if (curr_col < Game::MAX_X) {
            if (c == '@' &&( index == 1 || index == 2)) {
                bombs.push_back(Bomb(false, curr_col, curr_row, -1));
                screen[curr_row][curr_col] = '@'; 
            }
            else if (c == '\\' && (index == 1 || index == 2)) {
                screen_switches[num_switches++] = Switch(curr_col, curr_row, false, false);
                screen[curr_row][curr_col] = '\\';
            }
            else if (c == 'L' && (index == 1 || index == 2)) {
                l_p.setX(curr_col);
                l_p.setY(curr_row);
                screen[curr_row][curr_col] = ' '; 
            }
            else if (c >= '1' && c <= '9' && (index == 1 || index == 2)) {
                screen_door = Door(curr_col, curr_row, c, 1, false);
                screen[curr_row][curr_col] = c;
            }
            
            else {
                screen[curr_row][curr_col] = c;
            }
            curr_col++;
        }

        
    }

    int last_row = (curr_row < Game::MAX_Y ? curr_row : Game::MAX_Y - 1);
    
    // add a closing frame
    // first line
    #pragma warning(suppress : 4996) // to allow strcpy
    strcpy(screen[0], std::string(Game::MAX_X, 'W').c_str());
    screen[0][Game::MAX_X] = '\n';
    
    // last line
    #pragma warning(suppress : 4996) // to allow strcpy
    strcpy(screen[last_row], std::string(Game::MAX_X, 'W').c_str());
    screen[last_row][Game::MAX_X] = '\0';
    
    // first col + last col
    for (int row = 1; row < last_row; ++row) {
        screen[row][0] = 'W';
        screen[row][Game::MAX_X - 1] = 'W';
        screen[row][Game::MAX_X] = '\n';
    }


    for (int i = 0; i < Game::MAX_Y; i++) {
        strcpy_s(screen_reset[i], Game::MAX_X + 1, screen[i]);
    }



    screen_legend = Legend(l_p, screen);

    //GEMINI
    while (!std::getline(screen_file,str).eof())
    {
        size_t pos = str.find(':');

        if (pos != std::string::npos) {
            firstPart = str.substr(0, pos);   
            secondPart = str.substr(pos + 1); 
        }

        if (firstPart == "NUM_KEYS")
        {
            getDoor().setNumKeyNeeded(std::stoi(secondPart));
        }

        if (firstPart == "LINKED_TO_SWITCHES")
        {
            getDoor().setLinkedToSwitches(std::stoi(secondPart));
        }

        if (firstPart == "SWITCHES_COMB_NEEDED")
        {
            int i = 0;
            while (secondPart[i] != '\0') {
                if (secondPart[i] != ',') {
                    screen_switches[i].setIsNeeded((int)secondPart[i]);
                    i++;
                }
            }
        }

        if (firstPart == "SPRING")
        {

        }
    }
    
}

