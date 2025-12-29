#include "Menu.h"

Menu::Menu(Screens& s) : screens(s) {}

// Handles user input and state transitions for non-playing game states
GameState Menu::run(GameState current_state, int& current_room_id, vector<Player>& players, char key)
{

    //GAME STATE IS MENU
    if (current_state == GameState::MENU)
    {
        bool not_vaild_over_screen = false;
        bool not_vaild_on_objects = false;
        // Start a new game
        if (key == '1')
        {
            cls();

            //Checks if the Legend point is valid
            for (int i = 1; i < 3; i++) 
            { 
                if (screens.getgame_screens()[i].get_screen_legend().get_over_the_screen())
                {
                    not_vaild_over_screen = true;
                }
                else if (screens.getgame_screens()[i].get_screen_legend().get_on_objects())
                {
                    not_vaild_on_objects = true;
                }
            }
            if (not_vaild_on_objects)
            {
                gotoxy(20, 10);
                cout << "Error: Legend is placed on live objects!";
                return GameState::MENU;
            }
            else if (not_vaild_over_screen)
            {
                gotoxy(18, 10);
                cout << "Error: Legend is placed out of screen bounds!";
                return GameState::MENU;
            }
            else
            {
                
                //RESET PLAYERS AND SCREENS
                for (auto& p : players) { p.reset(); }
                for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(players); }
                current_room_id = 1;
                
                screens.getgame_screens()[current_room_id].draw();
                return GameState::PLAYING;
            }
            
        }
        // EXIT the game
        if (key == '9')
        {
            return GameState::EXIT;
        }
        // Go to instructions screen
        if (key == '8')
        {
            cls();
            current_room_id = 4; //4 = INSTRUCTIONS
            screens.getgame_screens()[current_room_id].draw();
            return GameState::INSTRUCTIONS;
        }
    }

    // STATE: INSTUCTIONS
    if (current_state == GameState::INSTRUCTIONS)
    {
        //go back to menu if player pressed ESC
        if (key == Keys::ESC)
        {
            current_room_id = 0; // MENU = 0
            screens.getgame_screens()[current_room_id].draw();
            return GameState::MENU;
        }
    }

    //STATE: PAUSED
    if (current_state == GameState::PAUSED)
    {
        // Return to menu if player pressed "H"
        if (key == 'H' || key == 'h')
        {
            current_room_id = 0; //MENU
            screens.getgame_screens()[MENU].draw();

            // Reset players' and room states for new game
            for (auto& p : players) { p.reset(); }
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(players); }
            return GameState::MENU;
        }
        // Resume game if player pressed ESC again
        else if (key == Keys::ESC)
        {
            cls();
            screens.getgame_screens()[current_room_id].draw();
            for (auto& p : players) {
                if (p.getIsActive()) {
                    p.draw();
                }
            }
            return GameState::PLAYING;
        }
    }

    //STATE: END GAME OR LOSE
    if (current_state == GameState::END_GAME || current_state == GameState::LOSE)
    {
        //go back to menu if player pressed ESC
        if (key == Keys::ESC)
        {
            current_room_id = 0;
            screens.getgame_screens()[current_room_id].draw();
            // Reset players' and room states for new game
            for (auto& p : players) { p.reset(); }
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(players); }
            return GameState::MENU;
        }
    }


    if (current_state == GameState::LOSE) {
        cls();
        screens.getgame_screens()[5].draw(); //show LOSE screen
    }
    // no state transition happened - keep same state;
    return current_state;
}