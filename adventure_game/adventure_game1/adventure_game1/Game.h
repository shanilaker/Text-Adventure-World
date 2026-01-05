#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include "Point.h"


enum Keys { ESC = 27 };

enum GameState {
    MENU = 0,
    PLAYING = 1,
    RIDDLE_ACTIVE = 2,
    PAUSED = 7,
    INSTRUCTIONS = 4,
    END_GAME = 5,
    LOSE = 6,
    EXIT = 9
};

enum Object {
    OBSTACLE = '*',
    BOMB = '@',
    RIDDLE = '?',
    C_SWITCH = '\\',
    SPRING = '#',
    O_SWITCH = '/',
    WALL = 'W',
    SPACE = ' ',
    TORCH = '!',
    KEY = 'K',

};

class Screens;
class Player;
class Screen;
using std::max, std::vector;

class Game
{
    int run_time = 0;

public:
    enum { MAX_X = 80, MAX_Y = 25 };

    //Empty ctor
    Game() {}

    //Get the run time of the game
    int getRuntime() const { return run_time; }

    //Set the run time of the game
    void setRuntime() { run_time++; }

    //Start the game
    void run();

    // Updates player positions, checks for movement triggers
    void updatePlayers(Screen& current_screen, vector<Player>& players, bool& riddle_triggered, Game& the_game, int current_room);

    // Prepares next screen and player positions for it
    void prepareNextRoom(Screen& next_screen, vector<Player>& players, const Point& spawnPoint, int current_room);

    // Calculate the next room to show based on players location with focus on second player to leave the room
    int calculateNextRoom(int current_room, vector<Player>& players, int& game_state);
};

