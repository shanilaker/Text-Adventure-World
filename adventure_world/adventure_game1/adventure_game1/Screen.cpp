#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Screen.h"
#include "Riddles.h"
#include<fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>    
#include <algorithm>

using std::string;

// Empty constructor
Screen::Screen()
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            screen[i][j] = Object::SPACE;
            screen_reset[i][j] = Object::SPACE;
        }
    }
}

// Resets screen for next gane
void Screen::reset(vector<Player>& players, bool first)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            screen[i][j] = screen_reset[i][j];
        }
    }
    
    if (legend_count > 0) {
        screen_legend.draw(screen, players, first);
        screen_legend.draw(screen_reset, players, first);

        for (auto& p : players) {
            if (p.getIsActive()) {
                screen_legend.update_values(p, *this);
            }
        }
    }

    for (int i = 0; i < riddles.size();i++)
    {
        riddles[i].reset();
    }

    for (int i = 0; i < bombs.size();i++)
    {
        bombs[i].reset();
    }
    for (int i = 0; i < obstacles.size();i++)
    {
        obstacles[i].reset();
    }
    players_moved = 0;
    for (auto& s : switches) {
        s.set_is_on();
    }

    for (auto& door : screen_doors) {
        door.setisActive();
        door.resetNumKeyNeeded();
        door.set_is_open();
    }
}

// Draws a specific (x,y) on the screen
void Screen::draw(const int& x, const int& y) const {
    if (!Game::silent_mode) {
        gotoxy(x, y);
        cout << screen[y][x];
    }
}

// Draws screen
void Screen::draw() const {
    if (!Game::silent_mode) {
        cls();
        gotoxy(0, 0);
        for (size_t i = 0; i < Game::MAX_Y - 1; ++i) {
            cout << screen[i] << endl;
        }
        cout << screen[Game::MAX_Y - 1];
        cout.flush();
    }
}


bool Screen::areSwitchesCorrect(char door_id) const {
    // Checks if all switches needed in the room are ON and rest are off
    for (const auto& s : switches) {
        if (s.getTargetDoorId() == door_id) {
            if (s.isOn() != s.isNeeded())
                return false;
        }
    }
    return true;
}

// Constructor 
Screen::Screen(const char* the_screen[Game::MAX_Y], vector<Door> _screen_doors, Point startPoint, Point endPoint, vector<Switch> the_switches, Legend _screen_legend, vector<Bomb>& _bombs, vector<Obstacle>& _obstacles, vector<Riddle>& _riddles, vector<Spring>& the_springs)
    : screen_doors(_screen_doors), startPos(startPoint), endPos(endPoint), switches(the_switches), screen_legend(_screen_legend), bombs(_bombs), obstacles(_obstacles), riddles(_riddles), springs(the_springs)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strncpy_s(screen[i], the_screen[i], Game::MAX_X);
        strncpy_s(screen_reset[i], the_screen[i], Game::MAX_X);
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
    return Object::SPACE; //out of range 
}

void Screen::setCharAt(const int& x, const int& y, const char& ch) {
    // checks if (x,y) is in screen boundries
    if (x >= 0 && x <= Game::MAX_X - 1 && y >= 0 && y <= Game::MAX_Y - 1 && screen[y] != nullptr) {
        screen[y][x] = ch;
    }
}

Spring* Screen::getSpringAt(int x, int y) {
    for (auto& s : springs) {
        // if found the spring in (x,y) - return it
        if (s.isSpringAt(x, y)) {
            return &s;
        }
    }
    return nullptr;
}

void Screen::restoreSprings() {
    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) {
            // If original screen had a spring and it's gone - put it back
            if (screen_reset[i][j] == Object::SPRING && screen[i][j] == Object::SPACE) {
                screen[i][j] = Object::SPRING;
                draw(j, i);
            }
        }
    }
}


void Screen::drawDark(vector<Player>& players) const {
    if (!Game::silent_mode) {
        int radius = 6;
        int legX = screen_legend.getPoint().getX();
        int legY = screen_legend.getPoint().getY();

        for (int i = 0; i < Game::MAX_Y; i++) {
            std::string line = "";
            for (int j = 0; j < Game::MAX_X; j++) {
                char current_map_char = screen[i][j];
                char char_to_draw = ' ';

                bool in_light = false;
                bool is_border = (i == 0 || i == Game::MAX_Y - 1 || j == 0 || j == Game::MAX_X - 1);
                bool is_torch = (current_map_char == Object::TORCH);
                bool is_legend = (i >= legY && i < legY + 6 && j >= legX && j < legX + 76);

                for (int p = 0; p < 2; p++) {
                    if (players[p].getIsActive() && !players[p].isWaiting()) {
                        int r = (players[p].getHeldItem() == Object::TORCH) ? radius : 0;
                        if (std::abs(players[p].getX() - j) <= r && std::abs(players[p].getY() - i) <= r) {
                            in_light = true;
                            break;
                        }
                    }
                }

                if (in_light || is_border || is_torch || is_legend) {
                    char_to_draw = current_map_char;
                    if (in_light) {
                        for (int p = 0; p < 2; p++) {
                            if (players[p].getIsActive() && !players[p].isWaiting() && players[p].getX() == j && players[p].getY() == i) {
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
}

//From tirgul with amir
void Screen::load(const std::string& filename, int index, Riddles& riddles_array)
{
    legend_count = 0;
    Point l_p;
    std::ifstream screen_file(filename);

    if (!screen_file.is_open()) {
        throw std::runtime_error("Critical Error: Screen file " + filename + " not found!");
    }

    int curr_row = 0;
    int curr_col = 0;
    char c;
    std::string str;

    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) screen[i][j] = Object::SPACE;
        screen[i][Game::MAX_X] = '\0';
    }

    while (screen_file.get(c) && curr_row < Game::MAX_Y) {

        if (c == '\n') {
            if (curr_col < Game::MAX_X) {
                // add spaces for missing cols
                #pragma warning(suppress : 4996) // to allow strcpy
                strcpy(screen[curr_row] + curr_col, std::string(Game::MAX_X - curr_col - 1, Object::SPACE).c_str());
            }
            curr_row++;
            curr_col = 0;
            continue;
        }


        if (curr_col < Game::MAX_X) {
            update_values(c, index, curr_col, curr_row, l_p);
            curr_col++;
        }


    }

    if (curr_row == 0) {
        throw std::runtime_error("Error: Screen file " + filename + " contains no data!");
    }

    int last_row = (curr_row < Game::MAX_Y ? curr_row : Game::MAX_Y - 1);

    createObstacbles(obstacles);

    for (auto& o : obstacles)
    {
        o.set_to_force_needed(static_cast<int>(o.get_body().size()));
        o.set_reset_force(static_cast<int>(o.get_body().size()));
    }


    findSpringsInScreen();

    createFrame(last_row);

    //Only to game boards add riddles
    if (index >= 1 && index <= 3)
    {
        for (int i = 0; i < Game::MAX_Y; i++) {
            for (int j = 0; j < Game::MAX_X; j++) {
                if (screen[i][j] == Object::RIDDLE)
                {
                    if (!riddles_array.getgame_riddles().empty())
                    {
                        Riddle& r = riddles_array.getgame_riddles().back();
                        r.setX(j);
                        r.setY(i);
                        r.set_room_connected(index);
                        riddles.push_back(r);
                        riddles_array.getgame_riddles().pop_back();
                    }
                }
            }
        }
    }


    for (int i = 0; i < Game::MAX_Y; i++) {
        strcpy_s(screen_reset[i], Game::MAX_X + 1, screen[i]);
    }

    screen_legend = Legend(l_p, screen);

    //GEMINI
    updateOutValues(screen_file, c);

    if (startPos.getX() == -1 || endPos.getX() == -1) {
        throw std::runtime_error("Error: Screen file " + filename + " is missing START_POS or END_POS!");
    }

    screen_file.close();
}

void Screen::createFrame(int last_row)
{
    // add a closing frame
    // first line
    #pragma warning(suppress : 4996) 
    strcpy(screen[0], std::string(Game::MAX_X, Object::WALL).c_str());
    screen[0][Game::MAX_X] = '\0';

    // last line
    #pragma warning(suppress : 4996) 
    strcpy(screen[last_row], std::string(Game::MAX_X, Object::WALL).c_str());
    screen[last_row][Game::MAX_X] = '\0';

    // first col + last col
    for (int row = 1; row < last_row; ++row) {
        screen[row][0] = Object::WALL;
        screen[row][Game::MAX_X - 1] = Object::WALL;
        screen[row][Game::MAX_X] = '\0';
    }
}

void Screen::update_values(char c, int index, int curr_col, int curr_row, Point& l_p)
{
    if (c == Object::BOMB && (index >= 1 && index <= 3)) {
        bombs.push_back(Bomb(false, curr_col, curr_row, -1));
        screen[curr_row][curr_col] = Object::BOMB;
    }

    else if (c == Object::C_SWITCH && (index >= 1 && index <= 3)) {
        switches.push_back(Switch(curr_col, curr_row, false, false));
        screen[curr_row][curr_col] = Object::C_SWITCH;
    }

    else if (c == 'L' && (index >= 1 && index <= 3)) {
        legend_count++;
        l_p.setX(curr_col);
        l_p.setY(curr_row);
        screen[curr_row][curr_col] = Object::SPACE;
    }

    else if (c >= '1' && c <= '9' && (index >= 1 && index <= 3)) {
        screen_doors.push_back(Door(curr_col, curr_row, c, 0, false));
        screen[curr_row][curr_col] = c;
    }

    else {
        screen[curr_row][curr_col] = c;
    }
}

void Screen::updateOutValues(std::ifstream& screen_file, char c)
{
    std::string line;
    std::string key;
    bool start_itr = true;
    while (std::getline(screen_file, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) continue;

        if (start_itr)
        {
            key = c + line.substr(0, pos);
            start_itr = false;
        }
        else
        {
            key = line.substr(0, pos);
        }


        std::string value = line.substr(pos + 1);

        if (key.find("DOOR_") == 0) {
            char d_id = key[5]; // gets the room id
            for (auto& d : screen_doors) {
                if (d.getChar() == d_id) {
                    if (key.find("_DEST") != string::npos)
                        d.setTargetRoom(stoi(value)); // sets target room (destination)
                    else if (key.find("_KEYS") != string::npos)
                        d.setNumKeyNeeded(stoi(value));
                    else if (key.find("_LINKED") != string::npos)
                        d.setLinkedToSwitches(stoi(value) != 0);
                }
            }
        }

        else if (key == "SWITCHES_COMB_NEEDED") {
            int switch_idx = 0;
            for (size_t i = 0; i < value.length() && switch_idx < switches.size(); i++) {
                if (value[i] == '0' || value[i] == '1') {
                    bool needed = (value[i] == '1');
                    switches[switch_idx].setIsNeeded(needed);
                    switch_idx++;
                }
            }
        }
        else if (key == "IS_DARK") {
            if (stoi(value) == 1) {
                setIsDark(true);
            }
        }

        else if (key == "START_POS") {
            size_t comma = value.find(',');
            startPos.setX(std::stoi(value.substr(0, comma)));
            startPos.setY(std::stoi(value.substr(comma + 1)));
        }
        else if (key == "END_POS") {
            size_t comma = value.find(',');
            endPos.setX(std::stoi(value.substr(0, comma)));
            endPos.setY(std::stoi(value.substr(comma + 1)));
        }

        if (key.find("_SWITCHES") != string::npos) {
            char d_id = key[5];
            std::stringstream ss(value);
            string index;
            while (std::getline(ss, index, ',')) {
                if (index.empty()) continue;
                int idx = std::stoi(index);
                if (idx >= 0 && idx < (int)switches.size()) {
                    switches[idx].setTargetDoorId(d_id);
                }
            }
        }
        else if (key.find("_COMB") != string::npos) {
            char d_id = key[5];
            std::stringstream ss(value);
            string state;
            for (auto& s : switches) {
                if (s.getTargetDoorId() == d_id) {
                    if (std::getline(ss, state, ',')) {
                        s.setIsNeeded(std::stoi(state) == 1);
                    }
                }
            }
        }
    }
}



bool Screen::isPlayerOverlappedWithLegend() const {
    return screen_legend.isPointInLegend(startPos.getX(), startPos.getY());
}



bool Screen::visited(int _x, int _y, vector<Point> visited)
{
    for (Point& p : visited)
    {
        if (p.getX() == _x && p.getY() == _y)
        {
            return true;
        }
    }
    return false;
}

void Screen::createObstacbles(vector<Obstacle>& _obstacles)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
            if (screen[i][j] == Object::OBSTACLE)
            {
                vector<Point> r_body;
                addBody(i, j, r_body);

                if (!r_body.empty()) {
                    _obstacles.push_back(Obstacle(j, i, 0, 0, 1, r_body));
                }
            }
        }
    }

    for (auto& obs : _obstacles) {
        for (const auto& p : obs.get_body()) {
            screen[p.getY()][p.getX()] = Object::OBSTACLE;
        }
    }
}

void Screen::addBody(int i, int j, vector<Point>& r_body)
{
    if (i < 0 || i >= Game::MAX_Y || j < 0 || j >= Game::MAX_X) return;
    if (screen[i][j] != Object::OBSTACLE) return;

    screen[i][j] = 'V';
    r_body.push_back(Point(j, i));

    addBody(i + 1, j, r_body);
    addBody(i - 1, j, r_body);
    addBody(i, j + 1, r_body);
    addBody(i, j - 1, r_body);
}

Door& Screen::getDoor(char door_number)
{
    for (auto& door : screen_doors) {
        if (door.getChar() == door_number)
            return door;
    }
    return screen_doors[0]; // shouldn't happen because if door is on screen it exists in screen_doors.
}

void Screen::findSpringsInScreen() {
    springs.clear();
    bool visited[Game::MAX_Y][Game::MAX_X + 1] = { false }; // arr to not count springs twice

    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) {

            // If found spring that wasn't scanned already
            if (screen[i][j] == Object::SPRING && !visited[i][j]) {
                int len = 0;
                Direction releaseDir = Direction::STAY;
                int startX = j;
                int startY = i;

                // If spring direction is right/left
                if (j + 1 < Game::MAX_X && screen[i][j + 1] == Object::SPRING) {
                    // calculate length of spring
                    while (j + len < Game::MAX_X && screen[i][j + len] == Object::SPRING) {
                        visited[i][j + len] = true;
                        len++;
                    }
                    // calculate release direction
                    if (j > 0 && screen[i][j - 1] == Object::WALL) { // if wall is from left - release direction is right
                        releaseDir = Direction::RIGHT;
                        startX = j;
                    }
                    else if (j + len < Game::MAX_X && screen[i][j + len] == Object::WALL) { // if wall is from right to spring- release direction is left
                        releaseDir = Direction::LEFT;
                        startX = j + len - 1;
                    }
                }
                // if spring direction is up/down
                else if (i + 1 < Game::MAX_Y && screen[i + 1][j] == Object::SPRING) {
                    while (i + len < Game::MAX_Y && screen[i + len][j] == Object::SPRING) {
                        visited[i + len][j] = true;
                        len++;
                    }
                    if (i > 0 && screen[i - 1][j] == Object::WALL) { //if wall is from above, release direction is down
                        releaseDir = Direction::DOWN;
                        startY = i;
                    }
                    else if (i + len < Game::MAX_Y && screen[i + len][j] == Object::WALL) { //if wall is from below, release direction is up
                        releaseDir = Direction::UP;
                        startY = i + len - 1;
                    }
                }
                // if spring is only 1 length
                else {
                    len = 1;
                    visited[i][j] = true;
                    // check where wall is to calculate release direction
                    if (j > 0 && screen[i][j - 1] == Object::WALL)
                        releaseDir = Direction::RIGHT;
                    else if (j + 1 < Game::MAX_X && screen[i][j + 1] == Object::WALL)
                        releaseDir = Direction::LEFT;
                    else if (i > 0 && screen[i - 1][j] == Object::WALL)
                        releaseDir = Direction::DOWN;
                    else if (i + 1 < Game::MAX_Y && screen[i + 1][j] == Object::WALL)
                        releaseDir = Direction::UP;
                }

                // If spring is not placed wrong, add it to screen.
                if (releaseDir != Direction::STAY) {
                    springs.push_back(Spring(startX, startY, len, releaseDir));
                }
            }
        }
    }
}

void Screen::saveState(std::ostream& out) const {
    for (int i = 0; i < Game::MAX_Y; ++i) {
        out << screen[i] << "\n";
    }

    out << screen_doors.size() << "\n";
    for (const auto& d : screen_doors) d.save(out);

    out << switches.size() << "\n";
    for (const auto& sw : switches) sw.save(out);

    out << bombs.size() << "\n";
    for (const auto& b : bombs) b.save(out);

    out << obstacles.size() << "\n";
    for (const auto& obs : obstacles) obs.save(out);

    out << riddles.size() << "\n";
    for (const auto& rid : riddles) rid.save(out);

    out << springs.size() << "\n";
    for (const auto& spr : springs) spr.save(out);
}

void Screen::loadState(std::istream& in) {
    std::string line;
    for (int i = 0; i < Game::MAX_Y; ++i) {
        std::getline(in, line);
        strncpy(screen[i], line.c_str(), Game::MAX_X);
        screen[i][Game::MAX_X] = '\0';
    }

    size_t size;

    in >> size; screen_doors.resize(size);
    for (auto& d : screen_doors) d.load(in);

    in >> size; switches.resize(size);
    for (auto& sw : switches) sw.load(in);

    in >> size; bombs.resize(size);
    for (auto& b : bombs) b.load(in);

    in >> size; obstacles.resize(size);
    for (auto& obs : obstacles) obs.load(in);

    in >> size; riddles.resize(size);
    for (auto& rid : riddles) rid.load(in);

    in >> size; springs.resize(size);
    for (auto& spr : springs) spr.load(in);

    in.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

