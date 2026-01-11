#include "Legend.h"
#include "Screen.h"
#include <string>

//Ctor
Legend::Legend() : p(Point(0, 0))
{
    //Update empty screen
    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) {
            l_screen[i][j] = Object::SPACE;
        }
        l_screen[i][Game::MAX_X] = '\0';
    }
}

//Ctor
Legend::Legend(Point _p, const char _incoming_screen[Game::MAX_Y][Game::MAX_X + 1]) : p(_p)
{
   //Update l_screen
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        for (int j = 0; j < Game::MAX_X; j++)
        {
          
            l_screen[i][j] = _incoming_screen[i][j];
        }
        l_screen[i][Game::MAX_X] = '\0'; 
    }

    int l_x = p.getX();
    int l_y = p.getY();

   //Check legend pos
    if (l_y > Game::MAX_Y - 6 || l_x > Game::MAX_X - 76)
    {
        over_the_screen = true;
    }

    //Check if the legend is on objects
    for (int j = l_y; j < l_y + 6; j++)
    {
        if (j < 0 || j >= Game::MAX_Y) continue;
        for (int i = l_x; i < l_x + 76; i++)
        {
            if (i < 0 || i >= Game::MAX_X) continue;

            char target = l_screen[j][i];
            if (target != Object::WALL && target != Object::SPACE)
            {
                on_objects = true;
            }
        }
    }
}

void Legend::update_values(const Player& p_ref, Screen& cur_screen)
{
    int roomID = p_ref.getCurrentRoomID();

    if (roomID >= 1 && roomID <= 3)
    {
        int row = (p_ref.get_char() == '$') ? p.getY() + 1 : p.getY() + 3;
        int l_x = p.getX();

        int currentLife = p_ref.getLife().getData();
        cur_screen.setCharAt(l_x + 23, row, std::to_string(currentLife)[0]);
        gotoxy(l_x + 23, row);
        std::cout << currentLife << "  ";
        const_cast<Player&>(p_ref).setLastLife(currentLife);

        int currentScore = p_ref.getScore().getData();
        std::string s = std::to_string(currentScore);
        for (int j = 0; j < 5; j++) {
            cur_screen.setCharAt(l_x + 44 + j, row, ' ');
            gotoxy(l_x + 44 + j, row);
            std::cout << ' ';
        }
        for (int j = 0; j < (int)s.length(); j++) {
            cur_screen.setCharAt(l_x + 44 + j, row, s[j]);
            gotoxy(l_x + 44 + j, row);
            std::cout << s[j];
        }
        const_cast<Player&>(p_ref).setLastScore(currentScore);

        char currentItem = p_ref.getHeldItem();
        char finalI = (currentItem == '\0') ? ' ' : currentItem;
        cur_screen.setCharAt(l_x + 61, row, finalI);
        gotoxy(l_x + 61, row);
        std::cout << finalI;
        const_cast<Player&>(p_ref).setLastItem(currentItem);
    }
}




void Legend::draw(char board[Game::MAX_Y][Game::MAX_X + 1], vector<Player>& players, bool first)
{
    int l_x = p.getX();
    int l_y = p.getY();

    for (int j = l_y; j < l_y + 6; j++)
    {
        if (j < 0 || j >= Game::MAX_Y) continue;
        for (int i = l_x; i < l_x + 76; i++)
        {
            if (i < 0 || i >= Game::MAX_X) continue;
            if (j == l_y || j == l_y + 5)
                board[j][i] = '-';
            else if (i == l_x || i == l_x + 75)
                board[j][i] = '|';
            else
                board[j][i] = ' ';
        }
    }

    auto writeAt = [&](int x, int y, const char* str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (x + i < Game::MAX_X && board[y][x + i] != '|')
                board[y][x + i] = str[i];
        }
        };

    const char* p1_header = "  PLAYER 1  >>  LIFE:           |  SCORE:        |  HOLD: ";
    const char* p2_header = "  PLAYER 2  >>  LIFE:           |  SCORE:        |  HOLD: ";
    writeAt(l_x + 1, l_y + 1, p1_header);
    writeAt(l_x + 1, l_y + 3, p2_header);

    for (int i = 0; i < (int)players.size() && i < 2; i++) {
        int row = (i == 0) ? l_y + 1 : l_y + 3;
        players[i].getLife().setX(l_x + 23);
        players[i].getLife().setY(row);
        players[i].getScore().setX(l_x + 44);
        players[i].getScore().setY(row);

        players[i].setLastLife(-99);
        players[i].setLastScore(-99);
        players[i].setLastItem('\1');

        if (first) {
            std::string lifeStr = std::to_string(players[i].getLife().getData());
            writeAt(l_x + 23, row, lifeStr.c_str());

            std::string scoreStr = std::to_string(players[i].getScore().getData());
            writeAt(l_x + 44, row, scoreStr.c_str());

            char item = players[i].getHeldItem();
            char itemStr[2] = { (item == '\0' ? ' ' : item), '\0' };
            writeAt(l_x + 61, row, itemStr);
        }
    }
}

bool Legend::isPointInLegend(int x, int y) const {
    int lx = p.getX();
    int ly = p.getY();
    return (x >= lx && x < lx + 76 && y >= ly && y < ly + 5);
}