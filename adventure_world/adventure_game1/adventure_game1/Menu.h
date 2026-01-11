#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Screens.h"
#include "Player.h"
#include <conio.h>
#include <ctime>        
#include <sstream>      
#include <iomanip>      
#include <string>       
#include <fstream>      
#include <iostream> 
#include <filesystem>

class Menu {
    Screens& screens;
    bool game_saved_flag = false;
public:

    //Ctor
    Menu(Screens& s);

    //Run the game
    GameState run(GameState current_state, int& current_room_id, vector<Player>& players, char key);

    //Testing if the game is valid
    GameState testing(bool not_vaild_over_screen, bool not_vaild_on_objects);

    //Create a file and save to it the all game arguments state
    std::string saveCurrentGame(int current_room, vector<Player>& players, Screens& screens);

    //Saving the game state
    GameState savingGameState(int& current_room_id, vector<Player>& players);
};

