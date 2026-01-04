#pragma once
#include <iostream>
#include <string.h>
#include "Riddle.h"
#include "Game.h"
#include "Door.h"
#include "Bomb.h"
#include "Switch.h"
#include"Obstacle.h"
#include "Legend.h"
#include "Spring.h"
#include "Riddles.h"

using std::cout, std::endl;


class Player;
class Screen 
{
	char screen[Game::MAX_Y][Game::MAX_X + 1];
	char screen_reset[Game::MAX_Y][Game::MAX_X + 1];
	vector<Door> screen_doors;
	int players_moved = 0;
	Point startPos{ 0, 0 };
	Point endPos{ 0, 0 };
	vector<Switch> switches;
	Legend screen_legend;
	vector<Bomb> bombs;
	vector<Obstacle> obstacles;
	vector<Riddle> riddles;
	vector<Spring> springs;
	bool is_dark = false;
	int legend_count = 0;

public:

	//Empty ctor
	Screen();

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y], vector<Door> screen_doors, Point startPoint, Point endPoint, vector<Switch> the_switches, Legend _screen_legend, vector<Bomb>& _bombs, vector<Obstacle>& _obstacles, vector<Riddle>& _riddles, vector<Spring>& the_springs);

	//Ctor
	Screen(const char* the_screen[Game::MAX_Y]);

	//Get the screen riddle
	vector<Riddle>& get_riddles(){ return riddles; }

	//Reset the screen
	void reset(vector<Player>& players);
	
	//Draw the all screen
	void draw() const;

	//Get the springs
	vector<Spring>& getSprings() { return springs; }

	// Get the number of springs
	size_t getNumSprings() const { return springs.size(); }

	// Set springs back after spring activated
	void restoreSprings();

	// Get the spring at specific point
	Spring* getSpringAt(int x, int y);

	// Set screen as dark
	void setIsDark(bool val) { is_dark = val; }

	// Check if screen is dark
	bool getIsDark() const { return is_dark; }

	// Draw screen as dark
	void drawDark(vector<Player>& players) const;

	//Draws a specific location on the screen
	void draw(const int& x, const int& y) const;

	//Set the char at this location
	void setCharAt(const int& x, const int& y, const char& ch);

	//Create the obstacles from the file we loaded
	void createObstacbles(vector<Obstacle>& obstacles);

	//Get the char at this location
	char getCharAt(const int& x, const int& y) const;

	//Set the door at this location
	Door& getDoor(char door_number);

	//Get the start point
	Point& getStartPos() { return startPos; }

	//Get the end point
	Point& EndPos() { return endPos; }

	//Get the number of players that moved
	int& get_players_moved() { return players_moved; }

	//Set the number of players that moved
	void set_player_moved(){ players_moved++; }

	//Reset the number of players that moved
	void reset_players_moved() { players_moved = 0; }

	//Get the obstacles
	vector<Obstacle>& get_obstacles() { return obstacles; }

	//Get the bombs
	vector<Bomb>& get_bombs() { return bombs; }

	//Get the screen board
	char (*getBoard())[Game::MAX_X + 1] { return screen; }

	//Get the switches
	vector<Switch>& getSwitches() { return switches; }

	//Get the number of switches
	size_t getNumSwitches() const { return switches.size(); }

	//Get the screen legend
	Legend& get_screen_legend() { return screen_legend; }

	//Checks if the switches is on
	bool areSwitchesCorrect(char door_id) const;

	//Load the screen from a file
	void load(const std::string& filename, int index, Riddles& riddles_array);

	//Update screen values
	void update_values(char c, int index, int curr_col, int curr_row, Point& l_p);

	//Update out of the screen values
	void updateOutValues(std::ifstream& screen_file, char c);

	//Create the screen frame
	void createFrame(int last_row);

	//Count the number of legend the screen designer add to the screen
	int get_legend_count() const { return legend_count; }

	//If the player is on the legand
	bool isPlayerOverlappedWithLegend() const;

	//Add the obstacle body to an obstacle on the screen
	void addBody(int i, int j, vector<Point>& r_body);

	//If we already visited this point
	bool visited(int _x, int _y, vector<Point> visited);

	// Locate and create the springs on the screen
	void findSpringsInScreen();
};


