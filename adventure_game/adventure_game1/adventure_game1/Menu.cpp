#include "Menu.h"

Menu::Menu(Screens& s) : screens(s) {}

// Handles user input and state transitions for non-playing game states
GameState Menu::run(GameState current_state, int& current_room_id, Player(&players)[2], char key)
{

    //GAME STATE IS MENU
    if (current_state == GameState::MENU)
    {
        // Start a new game
        if (key == '1')
        {
            cls();
            //RESET PLAYERS AND SCREENS
            for (auto& p : players) { p.reset(); }
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(); }

            current_room_id = 1;
            screens.getgame_screens()[current_room_id].draw();
            return GameState::PLAYING;
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
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(); }
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
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(); }
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