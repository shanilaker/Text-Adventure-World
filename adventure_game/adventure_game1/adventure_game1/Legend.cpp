#include "Legend.h"
#include "Screen.h"
#include <string>

//Ctor
Legend::Legend() : p(Point(0, 0))
{
    //Update empty screen
    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) {
            l_screen[i][j] = ' ';
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
            if (target != 'W' && target != ' ')
            {
                on_objects = true;
            }
        }
    }
}

//Update the legend values
void Legend::update_values(char ch, vector<Player>& players)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        //Update onlt the player that change his values
        if (players[i].get_char() == ch)
        {
            int row = (i == 0) ? p.getY() + 1 : p.getY() + 3;
            int holdX = p.getX() + 61; 

            gotoxy(holdX, row);

            
            char itemToShow = players[i].getHeldItem();
            if (itemToShow == '\0') {
                std::cout << ' ';
            }
            else {
                std::cout << itemToShow;
            }

            break;
        }
    }
}

//Draw the legend
void Legend::draw(char board[Game::MAX_Y][Game::MAX_X + 1], vector<Player>& players)
{
    int l_x = p.getX();
    int l_y = p.getY();

    //Create the frame
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

    //GEMINI
    auto writeAt = [&](int x, int y, const char* str) {
        if (y < 0 || y >= Game::MAX_Y) return;
        for (int i = 0; str[i] != '\0'; i++) {
            if (x + i >= 0 && x + i < Game::MAX_X && board[y][x + i] != '|') {
                board[y][x + i] = str[i];
            }
        }
        };

    const char* p1_header = "  PLAYER 1  >>  LIFE:          |  SCORE:        |  HOLD: ";
    const char* p2_header = "  PLAYER 2  >>  LIFE:          |  SCORE:        |  HOLD: ";

    writeAt(l_x + 1, l_y + 1, p1_header);
    writeAt(l_x + 1, l_y + 3, p2_header);

    for (int i = 0; i < 2; i++) {
        int row = (i == 0) ? l_y + 1 : l_y + 3;

        
        int lifeX = l_x + 23;
        int scoreX = l_x + 44;
        int holdX = l_x + 61;

        players[i].getLife().setX(lifeX);
        players[i].getLife().setY(row);

        players[i].getScore().setX(scoreX);
        players[i].getScore().setY(row);

       
        writeAt(lifeX, row, std::to_string(players[i].getLife().getData()).c_str());
        writeAt(scoreX, row, std::to_string(players[i].getScore().getData()).c_str());

        char itemStr[2] = { players[i].getHeldItem(), '\0' };
        writeAt(holdX, row, itemStr);
    }
}