#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include "Point.h"
#include "Results.h"
#include "Steps.h"
#include <fstream>
#include <map>
#include "utils.h"

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
protected:
    int run_time = 0;
    int game_state = MENU;
    bool validation_failed = false;
    virtual char getInput() = 0;
    virtual void doSleep() const = 0;
public:
    enum { MAX_X = 80, MAX_Y = 25 };

    virtual void recordEvent(GameEvent type, int data = 0) = 0;

    //Empty ctor
    Game() {}

    virtual ~Game() = default;

    virtual bool shouldShowMenu() const { return true; }

    virtual void checkValidation(int) {}

    //Get the run time of the game
    int getRuntime() const { return run_time; }

    //Set the run time of the game
    void setRuntime() { run_time++; }

    bool isValidationFailed() const { return validation_failed; }

    //Start the game
    void run();

    // Updates player positions, checks for movement triggers
    void updatePlayers(Screen& current_screen, vector<Player>& players, bool& riddle_triggered, Game& the_game, int current_room);

    // Prepares next screen and player positions for it
    void prepareNextRoom(Screen& next_screen, vector<Player>& players, const Point& spawnPoint, int current_room);

    // Calculate the next room to show based on players location with focus on second player to leave the room
    int calculateNextRoom(int current_room, vector<Player>& players);
};



class HumanInputGame : public Game {
    bool is_save_mode;
    Steps stepsTracker;
    Results resultsTracker;

public:
    //Ctor
    HumanInputGame(bool save) : is_save_mode(save) { }

    //Dtor
    ~HumanInputGame();//

    // Saves a game event to the result tracker
    virtual void recordEvent(GameEvent type, int data = 0) override;

    // Gets real-time keyboard press and records it if save mode is enabled
    virtual char getInput() override;
    
    // Writes the saved steps and results to the steps and results files.
    void SaveGame();
    
    // Pauses the execution to control the game speed for human play
    virtual void doSleep() const override { Sleep(80); }
};

class FileInputGame : public Game {
    bool is_silent_mode;
    Steps stepsLibrary;
    Results resultsCheck;

public:
    //Ctor
    FileInputGame(bool silent);

    // Gets the next key from the steps file based on current run_time
    virtual char getInput() override { return stepsLibrary.popNextKey(run_time); }

    // Controls replay speed; runs at maximum speed in silent mode
    virtual void doSleep() const override { (is_silent_mode) ? Sleep(0) : Sleep(40); }

    // Prevents the main menu from showing during a load mode
    virtual bool shouldShowMenu() const override { return false; }

    // Validates a current event against the result file; triggers mismatch on failure
    virtual void recordEvent(GameEvent type, int data = 0) override;

    // Checks for any events that were skipped or missed in the current execution 
    virtual void checkValidation(int current_iter) override;

private:
    // Converts a GameEvent enum value to its string representation for display
    std::string getEventName(GameEvent type) const;

    // Formats event-specific data into a readable string for error logs
    std::string formatEventData(GameEvent type, int data) const;

    // Handles and displays detailed error reports when the game is different from the file
    void handleMismatch(GameEvent expectedType, int expectedTime, const std::string& errorMsg, int expectedData, int actualData = -1, GameEvent actualType = (GameEvent)-1);
};