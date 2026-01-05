#pragma once
#include <iostream>
#include "utils.h"
#include "Direction.h"
#include "Game.h"
#include "Key.h"

class Screens;
class Screen;
class Door;
class Switch;
class Player 
{
	int x = 1, y = 1;
	int diff_x = 0, diff_y = 0;
	char ch = '*';
	static constexpr size_t NUM_KEYS = 6;
	char held_item = '\0';
	char keys[NUM_KEYS] = {};
	int current_room_id = 0;
	bool just_disposed = false;
	bool is_active = true;
	int reset_valueX = -1;
	int reset_valueY = -1;
	int diff_valueX  = -1;
	int diff_valueY = -1;
	int solvedRiddle = -2;
	bool moved_obstacle = false;
	Direction p_dir = Direction::STAY;
	Point life;
	Point score;
	static vector<Player> players;

	int boost_count = 0;
	int boost_speed = 1;
	int boost_time = 0;
	Direction boost_dir = Direction::STAY;

public:
	
	//Empty ctor
	Player(){}

	//Ctor
	Player(int x1, int y1, int diffx, int diffy, char c, const char(&the_keys)[NUM_KEYS + 1], int room_id, int riddleSolved);

	//reset the player values
	void reset();

	//Set the players
	void set_players(vector<Player>& _players) { players = _players; }

	//Take the key if can
	bool take_key(Screen& cur_screen, const int& next_x, const int& next_y);

	//Associate with a bomb
	bool move_to_bomb(const int& next_x, const int& next_y, Screen& cur_screen);

	//Associate with a door
	bool move_to_door(Door& door, Screen& cur_screen);

	//Associate with a riddle
	bool move_to_riddle(const int& next_x, const int& next_y, Screen& cur_screen);

	//Associate with a obstacle
	bool move_to_obstacle(Screen& cur_screen, vector<Player>& _players, int _x, int _y);

	//Associate with a switch
	bool move_to_switch(const int& next_x, const int& next_y, Screen& cur_screen);

	//Check if need to kill and do it accordingly
	void checkAndkill(int bomb_x, int bomb_y, int& game_state);

	//Draw the player
	void draw() const;

	//Draw c in x, y
	void draw(const char& c) const;

	//Get the solvedRiddle
	int getsolvedRiddle() const { return solvedRiddle; }

	//Set the solvedRiddle
	void setsolvedRiddle(int value) { solvedRiddle = value; }

	//Get if the player is active
	bool isActive() const { return is_active; }

	//Deactivates the player
	void kill();

	//Move the player
	bool move(Screen& cur_screen, Game the_game, Player& other_player);

	//Set the player's direction
	void setDirection(Direction dir);

	//Set the player's life
	void setLife(int value) { life.setData(value); }

	//Handle collision with other objects
	bool handleCollision(char target_char, int next_x, int next_y, Screen& cur_screen);

	//Set the player's Score
	void upScore() { score.setData(score.getData() + 15); }

	//Set the player's Score
	void downScore() { score.setData(score.getData() - 20); }

	//Get the player's life
	Point getLife() const { return life; }

	//Get the player's Score
	Point getScore() const { return score; }

	//Handles player movement based on the key pressed
	void handleKeyPressed(const char& key_pressed);

	//Get the x
	int getX() const { return x; }

	//Get the y
	int getY() const { return y; }
	
	//Get the current room the player is in
	int getCurrentRoomID() const { return current_room_id; }
	
	//Set the position of the player
	void setPosition(const Point& start);

	//Set the current room the player is in
	void setCurrentRoomID(int new_room_id) { current_room_id = new_room_id; }

	//Changes the player's position for future transition to a new screen
	void hideForTransition();

	//return if the player is waiting for future transition to a new screen
	bool isWaiting()const{ return x == -1 && y == -1; }

	//Get the diffx
	int getDiffx() const { return diff_x; }

	//Get the diffy
	int getDiffy() const { return diff_y; }

	//Set if the palyer Just Disposed
	void setJustDisposed(bool val) { just_disposed = val; }

	//Set if the palyer Just Disposed
	void set_moved_obstacle(bool val) { moved_obstacle = val; }

	//Get JustDisposed
	bool getJustDisposed() const { return just_disposed; }

	//Get the item the player holds
	char getHeldItem() const { return held_item; }

	//Set the item the player holds
	void setHeldItem(char item, Screen& cur_screen);

	//Return if the player holds an item
	bool hasItem() const { return held_item != '\0'; }

	//Get if the player is active
	bool getIsActive() const { return is_active; }

	//Get the player's sign
	char get_char() const { return ch; }

	//Get the opposite direction of a given direction
	Direction getOppositeDirection(Direction dir);

	// Get the remaining time of boost
	int getBoostTime() const { return boost_time; }

	// Get the amount of speed boost
	int getBoostSpeed() const { return boost_speed; }

	// Get the direction of the boost
	Direction getBoostDir() const { return boost_dir; }

	// Set the speed, time and direction of the boost
	void setBoost(int speed, int time, Direction dir);

	// Associate with a spring
	bool move_to_spring(const int& next_x, const int& next_y, Screen& cur_screen);

};

