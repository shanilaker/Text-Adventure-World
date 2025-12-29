#include "Riddle.h"
#include "Screen.h"

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
void Riddle::checkRiddleAnswer(Screen& cur_screen, Game& the_game, char key, vector<Player>& players)
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
                    if (p.getIsActive()){
                        if (p.getsolvedRiddle() == -1){
                            p.setsolvedRiddle(1);
                        }

                        if (!p.isWaiting()){
                            p.draw(' ');
                            //p.move(cur_screen, the_game);
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
        cur_screen.get_screen_legend().update_values(p.get_char(), players);
    }

}

void Riddle::reset()
{
    is_active = true;
    activated = false;
}


