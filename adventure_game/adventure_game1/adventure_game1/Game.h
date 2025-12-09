#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

class Screen;
enum Keys { ESC = 27 };

enum GameState {
    MENU = 0,
    PLAYING = 1,
    RIDDLE_ACTIVE = 2,
    PAUSED = 3,
    INSTRUCTIONS = 4,
    END_GAME = 5,
    LOSE = 6,
    EXIT = 9
};

class Screens;
class Player;

using std::max;

class Game
{
    int run_time = 0;

public:
	enum { MAX_X = 80, MAX_Y = 25 };

    //Empty ctor
    Game(){}

    //Get the run time of the game
    int getRuntime() const{ return run_time; }

    //Set the run time of the game
    void setRuntime(){ run_time++; }

    //Start the game
    void run();

    // Updates player positions, checks for movement triggers
    void updatePlayers(Screen& current_screen, Player(&players)[2], bool& riddle_triggered, Game& the_game);

    // Prepares next screen and player positions for it
    void prepareNextRoom(Screen& next_screen, Player(&players)[2]);
};

