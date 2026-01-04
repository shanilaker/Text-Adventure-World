#include "Game.h"
#include "Screens.h"
#include "Player.h"
#include "Menu.h"
#include "Riddle.h"


void Game::run()
{
	hideCursor();
	Screens screens; // Initialize the screens manager
	Menu menu_handler(screens); // Initialize the menu handler with access to screens

	int game_state = MENU;
	int current_room = MENU;

	screens.getgame_screens()[MENU].draw();
	// Initialize two players with their start positions, symbols and keysets
	vector<Player> players;
	players.push_back(Player(20, 20, 0, 0, '$', "wdxase", 0, false));
	players.push_back(Player(10, 10, 0, 0, '&', "ilmjko", 0, false));

	for (auto& p : players)
	{
		p.set_players(players);
	}


	

	//Main game loop until player chose EXIT
	while (game_state != GameState::EXIT) {

		auto& current_screen = screens.getgame_screens()[current_room];
		if (_kbhit()) // Check for keyboard input
		{
			char key = (char)_getch(); // Get the pressed key
			bool state_changed = false;
			//Handler for menu and non-playing states 
			if (game_state == MENU || game_state == INSTRUCTIONS || game_state == END_GAME || game_state == LOSE || game_state == PAUSED)
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
						riddle.checkRiddleAnswer(current_screen, key, players);
						riddle.setActivated(false);
					}

				}
				game_state = PLAYING;
			}
			// Handle players key presses
			else if (game_state == PLAYING && !state_changed) {
				//Pause
				if (key == Keys::ESC) {
					gotoxy(4, 10);
					cout << "Game paused, press ESC again to continue or H to go back to the main menu";
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
						game_state = RIDDLE_ACTIVE;
						riddle.Show_Riddle();
						break;
					}
				}
			}
			// Check if room was completed (both players moved)
			bool current_room_is_empty = true;
			for (auto& p : players) {
				if (p.getIsActive() && !p.isWaiting() && p.getCurrentRoomID() == current_room) {
					current_room_is_empty = false;
					break;
				}
			}

			if (current_room_is_empty && current_screen.get_players_moved() > 0) {
				cls();

				int prev_room = current_room;
				int next_room_index = -1;

				bool all_at_end = true;
				for (auto& p : players) {
					if (p.getIsActive() && p.getCurrentRoomID() != 4) {
						all_at_end = false;
					}
				}

				if (all_at_end) {
					next_room_index = 4;
					game_state = END_GAME;
				}
				else {
					for (auto& p : players) {
						if (p.getIsActive() && p.getCurrentRoomID() != prev_room) {
							next_room_index = p.getCurrentRoomID();
						}
					}
				}

				if (next_room_index != -1) {
					screens.getgame_screens()[prev_room].reset_players_moved(); // reset previous room counter of players moved

					current_room = next_room_index;
					auto& next_screen = screens.getgame_screens()[current_room];

					Point spawnPoint = (current_room > prev_room) ? next_screen.getStartPos() : next_screen.EndPos();

					// Check if the next room is the end game screen
					if (game_state == END_GAME) {
						next_screen.draw();
					}
					else {
						// Prepare the next playing room
						prepareNextRoom(next_screen, players, spawnPoint, current_room);
					}
				}
			}
			setRuntime(); // Update game runtime/cycles
		}
		Sleep(80);
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
			Player& other = (&p == &players[0]) ? players[1] : players[0];
			// Clear player's previous position
			if (!p.isWaiting() && !p.getJustDisposed()) {
				p.draw(' ');
			}
			// Move the player
			if (p.move(current_screen, the_game,other)) {

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

// Prepares next screen and player positions for it 
void Game::prepareNextRoom(Screen& next_screen, vector<Player>& players, const Point& spawnPoint, int current_room)
{
	next_screen.draw();
	for (auto& p : players)
	{
		if (p.getIsActive())
		{
			if (p.getCurrentRoomID() == current_room)
			{
				// Set player position to room's default coordination and draw it
				p.setPosition(spawnPoint);
				p.setDirection(Direction::STAY);
				p.draw();
			}
			else {
				// if player is active but not in this room,  hide it.
				p.hideForTransition();
			}
		}
	}
}