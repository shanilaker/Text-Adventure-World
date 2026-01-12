#include "Menu.h"

Menu::Menu(Screens& s) : screens(s) {}

GameState Menu::run(GameState current_state, int& current_room_id, vector<Player>& players, char key)
{
    if (current_state == GameState::MENU)
    {
        bool not_vaild_over_screen = false;
        bool not_vaild_on_objects = false;

        if (key == '1')
        {
            cls();
            GameState test_result = testing(not_vaild_over_screen, not_vaild_on_objects);

            if (test_result == GameState::MENU) {
                return GameState::MENU;
            }

            //Start the game
            current_room_id = 1;
            auto& start_screen = screens.getgame_screens()[current_room_id];

            for (auto& p : players) {
                p.reset();
                p.setCurrentRoomID(current_room_id);
                p.setPosition(start_screen.getStartPos());
            }
            for (int i = 1; i < 4; i++) {
                if (i == 1)
                {
                    screens.getgame_screens()[i].reset(players,true);
                }

                else
                {
                    screens.getgame_screens()[i].reset(players, false);
                }
                
            }

            start_screen.draw();

            for (auto& p : players) {
                start_screen.get_screen_legend().update_values(p, start_screen);
            }

            for (auto& p : players) {
                p.draw();
            }

            return GameState::PLAYING;
        }

        if (key == '9')
        {
            return GameState::EXIT;
        }

        if (key == '8')
        {
            cls();
            current_room_id = GameState::INSTRUCTIONS;
            screens.getgame_screens()[current_room_id].draw();
            return GameState::INSTRUCTIONS;
        }

        if (key == '2') 
        {
            return savingGameState(current_room_id, players);
        }
    }

    if (current_state == GameState::INSTRUCTIONS)
    {
        if (key == Keys::ESC)
        {
            current_room_id = GameState::MENU;
            screens.getgame_screens()[current_room_id].draw();
            return GameState::MENU;
        }
    }

    if (current_state == GameState::PAUSED)
    {
        //If we paused beacuse we saved state - act accordingly
        if (game_saved_flag)
        {
            //Retrun to the current state in the recent game
            if (key == Keys::ESC)
            {
                game_saved_flag = false;
                cls();
                auto& curr_screen = screens.getgame_screens()[current_room_id];
                curr_screen.draw();
                for (auto& p : players) if (p.getIsActive()) p.draw();
                return GameState::PLAYING;
            }
            return GameState::PAUSED;
        }

        //If we paused beacuse we want saved state - act accordingly
        if (key == 'S' || key == 's')
        {
            //Saves the state
            std::string fileName = saveCurrentGame(current_room_id, players, screens);
            game_saved_flag = true;

            cls();
            gotoxy(10, 11);
            std::cout << "Game saved to " << fileName << "! Press ESC to resume.";
            return GameState::PAUSED;
        }

        //If we want to go back to the menu screen
        else if (key == 'H' || key == 'h')
        {
            current_room_id = MENU;
            screens.getgame_screens()[MENU].draw();
            for (auto& p : players) p.reset();
            return GameState::MENU;
        }

        //Returning from the paused state to the game
        else if (key == Keys::ESC)
        {
            cls();
            auto& curr_screen = screens.getgame_screens()[current_room_id];
            curr_screen.draw();
            for (auto& p : players) if (p.getIsActive()) p.draw();
            return GameState::PLAYING;
        }
    }

    if (current_state == GameState::END_GAME || current_state == GameState::LOSE)
    {
        if (key == Keys::ESC)
        {
            current_room_id = GameState::MENU;
            cls();
            screens.getgame_screens()[current_room_id].draw();
            for (auto& p : players) { p.reset(); }
            for (int i = 1; i < 4; i++) { 
                if (i == 1)
                {
                    screens.getgame_screens()[i].reset(players, true);
                }

                else
                {
                    screens.getgame_screens()[i].reset(players, false);
                }
            }
            return GameState::MENU;
        }
    }

    if (current_state == GameState::LOSE) {
        cls();
        screens.getgame_screens()[GameState::LOSE].draw();
    }

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
    int ridlles_files = screens.getTotalRiddleScreensCount();
    if (total_riddles > ridlles_files)
    {
        gotoxy(15, 10);
        std::cout << "Error: Too many riddles in the game! (Max: " << ridlles_files<< ", Found: " << total_riddles << ")";
        return GameState::MENU;
    }

    //Checks if the Legend point is valid
    for (int i = 1; i < 4; i++)
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


std::string Menu::saveCurrentGame(int current_room, vector<Player>& players, Screens& _screens) {

    //Gemini helped - save to a file with a name by the format of day-month_hour-minutes
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << "save_" << std::put_time(&tm, "%d-%m_%H-%M") << ".txt";
    std::string fileName = ss.str();

    std::ofstream outFile(fileName);
    if (outFile.is_open()) {

        //Saves the current room we at
        outFile << current_room << std::endl;
        
        //Saves the players info
        for (auto& p : players) {
            p.save(outFile); 
        }

        //Sasves the screens text
        for (auto& s : _screens.getgame_screens()) {
            s.saveState(outFile); 
        }
        outFile.close();
    }
    return fileName;
}


GameState Menu::savingGameState(int& current_room_id, vector<Player>& players)
{
    namespace fs = std::filesystem;
    std::vector<std::string> saveFiles;

    for (const auto& entry : fs::directory_iterator(".")) {
        std::string filename = entry.path().filename().string();
        if (filename.substr(0, 5) == "save_" && entry.path().extension() == ".txt") {
            saveFiles.push_back(filename);
        }
    }

    if (saveFiles.empty()) {
        cls();
        gotoxy(14, 11);
        std::cout << "No save states found! Press ESC to return to menu...";
        int exit_key = 0;
        while (exit_key != 27) { exit_key = _getch(); }
        screens.getgame_screens()[MENU].draw();
        return GameState::MENU;
    }

    cls();
    //Print the list of saved states
    std::cout << "--- SELECT A SAVE STATE TO LOAD ---\n";
    for (size_t i = 0; i < saveFiles.size(); ++i) {
        std::cout << i + 1 << ". " << saveFiles[i] << "\n";
    }
   
    std::cout << "\nEnter file number to load, or 0 to cancel: ";

    int choice = 0;
    bool validChoice = false;

    //Wait for the user to enter valid choice
    while (!validChoice) {
        if (!(std::cin >> choice)) {
            std::cout << "Error: Please enter a valid number: ";
            std::cin.clear(); 
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }

        //Like ESC
        if (choice == 0) {
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            screens.getgame_screens()[MENU].draw();
            return GameState::MENU; //
        }

        if (choice < 1 || choice >(int)saveFiles.size()) {
            std::cout << "Invalid number! Please choose between 1 and " << saveFiles.size() << " (or 0 to cancel): ";
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        else {
            validChoice = true;
        }
    }

    
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    int idx = choice - 1;

    std::ifstream inFile(saveFiles[idx]);
    if (inFile) {

        //Load the state to the game
        inFile >> current_room_id;
        for (auto& p : players) {
            p.load(inFile);
            p.setCurrentRoomID(current_room_id);
        }

        
        inFile.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        for (auto& s : screens.getgame_screens()) {
            s.loadState(inFile);
        }
        inFile.close();

        cls();
        auto& loaded_screen = screens.getgame_screens()[current_room_id];
        loaded_screen.draw();

        for (auto& p : players) {
            if (p.getIsActive()) {
                if (loaded_screen.get_legend_count() > 0) {
                    loaded_screen.get_screen_legend().update_values(p, loaded_screen);
                }
                p.draw();
            }
        }
        return GameState::PLAYING;
    }

    screens.getgame_screens()[MENU].draw();
    return GameState::MENU;
}