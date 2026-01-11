#include "Game.h"
#include "Screens.h"
#include "Player.h"
#include "Menu.h"
#include "Riddle.h"
#include <iostream>

void Game::run()
{
	hideCursor();
	Screens screens; // Initialize the screens manager
	Menu menu_handler(screens); // Initialize the menu handler with access to screens
	int current_room = MENU;

	
	// Initialize two players with their start positions, symbols and keysets
	vector<Player> players;
	players.push_back(Player(20, 20, 0, 0, '$', "wdxase", 0, false));
	players.push_back(Player(10, 10, 0, 0, '&', "ilmjko", 0, false));

	if (!shouldShowMenu()) {
		game_state = PLAYING;
		current_room = 1;
		auto& start_screen = screens.getgame_screens()[current_room];

		for (auto& p : players) {
			p.reset();
			p.setPosition(start_screen.getStartPos());
		}
		for (int i = 1; i < 4; i++) {
			if (i == 1)
				screens.getgame_screens()[i].reset(players, true);
			else
				screens.getgame_screens()[i].reset(players, false);
		}
		start_screen.draw();

		for (auto& p : players) {
			start_screen.get_screen_legend().update_values(p, start_screen);
			p.draw();
		}

	}
	else {
		screens.getgame_screens()[MENU].draw();
	}

	//Main game loop until player chose EXIT
	while (game_state != GameState::EXIT) {

		auto& current_screen = screens.getgame_screens()[current_room];
		char key = getInput();// Check for keyboard input and get the pressed key

		if (key != '\0')
		{
			bool state_changed = false;
			//Handler for menu and non-playing states 
			if (shouldShowMenu() && (game_state == MENU || game_state == INSTRUCTIONS || game_state == END_GAME || game_state == LOSE || game_state == PAUSED))
			{
				GameState next_state = menu_handler.run((GameState)game_state, current_room, players, key);
				// Check if the game state has changed
				if ((int)next_state != game_state) {
					game_state = (int)next_state;
					state_changed = true;
				}
			}
			// riddle state is active, check the player's answer
			if (game_state == RIDDLE_ACTIVE) {
				for (auto& riddle : current_screen.get_riddles())
				{
					if (riddle.getActivated())
					{
						riddle.checkRiddleAnswer(current_screen, key, players, *this);
						riddle.setActivated(false);
					}

				}
				game_state = PLAYING;
			}
			// Handle players key presses
			else if (game_state == PLAYING && !state_changed) {

				// Pause and ask the user how he wants to continue
				if (key == Keys::ESC && shouldShowMenu()) {
					gotoxy(15, 10);
					cout << "Game paused: ESC to continue, H for Menu, S to SAVE";
					game_state = PAUSED;
				}
				else {
					for (auto& p : players) {
						if (p.getIsActive()) {
							p.handleKeyPressed(key); // Handle player movement keys
						}
					}
				}
			}
		}


		if (game_state == PLAYING) {
			bool riddle_triggered = false;
			// Check and update if bomb is activated, handle explosion
			for (auto& bomb : current_screen.get_bombs())
			{
				bomb.explodeBomb(current_screen, *this, game_state, players);
			}

			// Update player positions, movement and check for triggers
			updatePlayers(current_screen, players, riddle_triggered, *this, current_room);
			cout.flush();
		
			// Handle riddle trigger event
			if (riddle_triggered) {
				for (auto& riddle : current_screen.get_riddles())
				{
					if (riddle.getisActive() && riddle.getActivated()) {
						recordEvent(GameEvent::RIDDLE_START, (int)riddle.get_player_activated());
						game_state = RIDDLE_ACTIVE;
						riddle.Show_Riddle();
						break;
					}
				}
			}
			// Check if room was completed (both players moved)
			int next_room = calculateNextRoom(current_room, players);
			if ((next_room != current_room)) {
				recordEvent(GameEvent::CHANGE_ROOM, next_room);
				cls();
				int prev_room = current_room;
				current_room = next_room;

				screens.getgame_screens()[prev_room].reset_players_moved();
				auto& next_screen = screens.getgame_screens()[current_room];

				
				Point spawnPoint = (current_room > prev_room) ? next_screen.getStartPos() : next_screen.EndPos();

				if (game_state == END_GAME) {
					next_screen.draw();
				}
				else {
					prepareNextRoom(next_screen, players, spawnPoint, current_room);
				}
			}
			checkValidation(run_time);
			setRuntime(); // Update game runtime
			
		}
		doSleep();
	}
	cls();
}

// Updates player positions, checks for movement triggers
void Game::updatePlayers(Screen& current_screen, vector<Player>& players, bool& riddle_triggered, Game& the_game, int current_room)
{
	//Update obstacle parameters
	for (auto& obstacle : current_screen.get_obstacles())
	{
		if (obstacle.get_is_moved() == false) {
			obstacle.set_to_force_needed(obstacle.get_reset_force());
			for (auto& p : players) {
				p.set_moved_obstacle(false);
			}
		}

	}

	for (auto& p : players)
	{
		if (p.getIsActive() && p.getCurrentRoomID() == current_room && !p.isWaiting()) {
			// Clear player's previous position
			if (!p.isWaiting() && !p.getJustDisposed()) {
				p.draw(Object::SPACE);
			}
			// Move the player
			if (p.move(current_screen, the_game, players)) {

				for (auto& riddle : current_screen.get_riddles())
				{
					if (riddle.getisActive())
					{
						riddle_triggered = true;
					}
				}
			}
			// Draw the player in new position
			if (!p.isWaiting()) {
				p.draw();
			}
		}

		// If room is dark, draw only parts that has light
		if (current_screen.getIsDark()) {
			current_screen.drawDark(players);
		}
	}


}


void Game::prepareNextRoom(Screen& next_screen, vector<Player>& players, const Point& spawnPoint, int current_room)
{
	next_screen.draw();	

	for (auto& p : players)
	{
		if (p.getIsActive())
		{
			p.setCurrentRoomID(current_room);
			if (next_screen.get_legend_count() > 0)
			{ 
				next_screen.get_screen_legend().update_values(p, next_screen);
			}
			
			if (p.getCurrentRoomID() == current_room)
			{
				p.setPosition(spawnPoint);
				p.setDirection(Direction::STAY);
				p.draw();
			}
			else {
				p.hideForTransition();
			}
		}
	}
}

int Game::calculateNextRoom(int current_room, vector<Player>& players)
{
	int room_to_follow = -1;

	for (auto& p : players) {
		if (p.getJustDisposed() && p.isWaiting()) {
			room_to_follow = p.getCurrentRoomID();
			p.setJustDisposed(false);
		}
	}

	bool current_room_is_empty = true;
	for (auto& p : players) {
		if (p.getIsActive() && !p.isWaiting() && p.getCurrentRoomID() == current_room) {
			current_room_is_empty = false;
			break;
		}
	}

	if (current_room_is_empty && room_to_follow != -1) {
		bool both_finished = true;
		for (auto& p : players) {
			if (p.getIsActive() && p.getCurrentRoomID() != END_GAME) {
				both_finished = false;
			}
		}

		if (room_to_follow == END_GAME && !both_finished) {
			for (auto& p : players) {
				if (p.getIsActive() && p.getCurrentRoomID() != END_GAME) {
					return p.getCurrentRoomID();
				}
			}
		}
		else if (room_to_follow == END_GAME && both_finished) {
			int total_score = players[0].getScore().getData() + players[1].getScore().getData();
			recordEvent(GameEvent::GAME_FINISHED, total_score);
			if (!shouldShowMenu()) {
				game_state = EXIT;
			}
			else {
				game_state = END_GAME;
			}
			if (auto* humanGame = dynamic_cast<HumanInputGame*>(this)) {
				humanGame->SaveGame();
			}
			return END_GAME;
		}
		else {
			return room_to_follow;
		}
	}

	return current_room;
}

