#include "Game.h"

int main(int argc, char* argv[]) {
    try {
        Game* the_game = nullptr;
        bool load = false;
        bool save = false;
        bool silent = false;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-load") 
                load = true;
            else if (arg == "-save") 
                save = true;
            else if (arg == "-silent") 
                silent = true;
        }

        if (load) {
            the_game = new FileInputGame(silent);
        }
        else if (save) {
            the_game = new HumanInputGame(true);
        }
        else {
            the_game = new HumanInputGame(false);
        }

        if (the_game) {
            the_game->run();

            if (the_game->isValidationFailed()) {}
            else if (load) {
                cls();
                std::cout << "Replay finished successfully! All events matched." << std::endl;
            }

            delete the_game; 
        }
    }
    catch (const std::exception& e) {
        system("cls");
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        std::cout << "Press Enter to close..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}