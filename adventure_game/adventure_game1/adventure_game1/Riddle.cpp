#include "Riddle.h"
#include "Screen.h"
#include<fstream>
#include <iostream>
#include <string>
#include <sstream>

// Riddle constructor
Riddle::Riddle(const char* r_text[Game::MAX_Y], int r_x, int r_y,int r_room_connected, char the_answer): x(r_x), y(r_y), room_connected(r_room_connected), answer(the_answer)
{
    for (int i = 0; i < Game::MAX_Y; i++)
    {
        strncpy_s(text[i], r_text[i], Game::MAX_X);
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

//Check if player's riddle answer is correct and update game accordingly
void Riddle::checkRiddleAnswer(Screen& cur_screen, char key, vector<Player>& players)
{
    for (auto& riddle : cur_screen.get_riddles())
    {
        if (riddle.getActivated())
        {
            if (key == riddle.getAnswer())
            {
                // If answer is correct, set solvedRiddle to 1 (SOLVED) and draw player on the game screen
                cls();
                cur_screen.draw();
                for (auto& p : players) {
                    if (p.getIsActive()) {
                        if (p.get_char() == riddle.get_player_activated())
                        {
                            p.upScore();
                        }

                        if (p.getsolvedRiddle() == -1) {
                            p.setsolvedRiddle(1);
                        }

                        if (!p.isWaiting()) {
                            p.draw(' ');
                            p.draw();
                        }
                    }
                }
                cout.flush();
                riddle.setisActive(false);
            }
            else
            {
                //If answer is incorrect, set solvedRiddle to 0 (NOT SOLVED) and draw player on the game screen, near the riddle
                cls();
                cur_screen.draw();
                for (auto& p : players) {
                    if (p.getIsActive())
                    {
                        if (p.get_char() == riddle.get_player_activated())
                        {
                            p.downScore();
                        }

                        if (p.getsolvedRiddle() == -1) {
                            p.setsolvedRiddle(0);
                        }
                        p.draw(' ');
                        p.draw();
                    }

                }
                cout.flush();
            }

            riddle.setActivated(false);
        }
    }

    for (auto& p : players)
    {
        cur_screen.get_screen_legend().update_values(p.get_char(), players, cur_screen);
    }

}

void Riddle::reset()
{
    is_active = true;
    activated = false;
}


//From tirgul with amir
void Riddle::load(const std::string& filename)
{
    Point l_p;
    std::ifstream screen_file(filename);
    if (!screen_file.is_open()) {
        throw std::runtime_error("Critical Error: Riddle file " + filename + " is missing!");
    }

    if (screen_file.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("Critical Error: Screen file " + filename + " is empty (no content found)!");
    }

    int curr_row = 0;
    int curr_col = 0;
    char c;
    std::string str;

    for (int i = 0; i < Game::MAX_Y; i++) {
        for (int j = 0; j < Game::MAX_X; j++) text[i][j] = Object::SPACE;
        text[i][Game::MAX_X] = '\0';
    }

    while (screen_file.get(c) && curr_row < Game::MAX_Y) {

        if (c == '\n') {
            if (curr_col < Game::MAX_X) {
                // add spaces for missing cols
                #pragma warning(suppress : 4996) // to allow strcpy
                strcpy(text[curr_row] + curr_col, std::string(Game::MAX_X - curr_col - 1, Object::SPACE).c_str());
            }
            curr_row++;
            curr_col = 0;
            continue;
        }

        if (curr_col < Game::MAX_X) {
            text[curr_row][curr_col] = c;
            curr_col++;
        }


    }
    //GEMINI
    while (std::getline(screen_file, str))
    {
        if (str.length() < 3) continue;

        updateOutValues(str, c);
    }

    screen_file.close();

    

    if (answer == '\0') {
        throw std::runtime_error("Error: Riddle " + filename + " is corrupted. No 'ANSWER:' found.");
    }
}

void Riddle::updateOutValues(std::string str, char c)
{
    std::string firstPart;
    std::string secondPart;

    int pos = -1;

    for (int j = 0; j < (int)str.length(); j++) {
        if (str[j] == ':') {
            pos = j;
            break;
        }
    }

    if (pos != -1) {
        firstPart = c + str.substr(0, pos);
        secondPart = str.substr(pos + 1);

        if (firstPart == "ANSWER")
        {
            answer = secondPart[0];
        }
        
    }
}




