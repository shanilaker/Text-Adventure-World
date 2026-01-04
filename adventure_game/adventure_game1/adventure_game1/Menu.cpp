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
            GameState test_result = testing(not_vaild_over_screen, not_vaild_on_objects);

            if (test_result == GameState::MENU) {
                return GameState::MENU;
            }
            
            current_room_id = 1;
            auto& start_screen = screens.getgame_screens()[current_room_id];

            //RESET PLAYERS AND SCREENS
            for (auto& p : players) { 
                p.reset(); 
                p.setPosition(start_screen.getStartPos());
            }
            for (int i = 1; i < 3; i++) { screens.getgame_screens()[i].reset(players); }
            
            start_screen.draw();
            start_screen.get_screen_legend().draw(start_screen.getBoard(), players);
            for (auto& p : players) {
                p.draw(); 
            }
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

GameState Menu::testing(bool not_vaild_over_screen, bool not_vaild_on_objects)
{
    for (int i = 1; i < 3; i++)
    {
        //If the players start position is out of the screen
        if (screens.getgame_screens()[i].getStartPos().getX() >= Game::MAX_X || screens.getgame_screens()[i].getStartPos().getY() >= Game::MAX_Y)
        {
            gotoxy(15, 10);
            std::cout << "Error: Player starts out of the screen erea in Screen " << i << "!";
            return GameState::MENU;
        }

        //If the players start position is on the legend
        if (screens.getgame_screens()[i].isPlayerOverlappedWithLegend())
        {
            gotoxy(15, 10);
            std::cout << "Error: Player starts inside Legend area in Screen " << i << "!";
            return GameState::MENU;
        }
    }

    //If there is no legend or more then one legend
    for (int i = 1; i < 3; i++)
    {
        int l_count = screens.getgame_screens()[i].get_legend_count();
        if (l_count != 1)
        {
            gotoxy(25, 10);
            if (l_count == 0) std::cout << "Error: Missing Legend in Screen " << i;
            else std::cout << "Error: Too many Legends in Screen " << i;
            return GameState::MENU;
        }
    }

    //If we have more '?' than riddles
    size_t total_riddles = screens.getTotalRiddlesCount();
    if (total_riddles > 6)
    {
        gotoxy(15, 10);
        std::cout << "Error: Too many riddles in the game! (Max: 6, Found: " << total_riddles << ")";
        return GameState::MENU;
    }

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

    //If the legend is on live objects
    if (not_vaild_on_objects)
    {
        gotoxy(20, 10);
        cout << "Error: Legend is placed on live objects!";
        return GameState::MENU;
    }

    //If the legend placed out of the screen 
    else if (not_vaild_over_screen)
    {
        gotoxy(18, 10);
        cout << "Error: Legend is placed out of screen bounds!";
        return GameState::MENU;
    }

    return GameState::PLAYING;
}