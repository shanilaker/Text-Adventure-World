#include "Game.h"


int main() {
    try {
        Game the_game;
        the_game.run();
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
