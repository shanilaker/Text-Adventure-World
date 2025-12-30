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

	screens.getgame_screens()[MENU].draw();
	// Initialize two players with their start positions, symbols and keysets
	vector<Player> players;
	players.push_back(Player(20, 20, 0, 0, '$', "wdxase", 0, false));
	players.push_back(Player(10, 10, 0, 0, '&', "ilmjko", 0, false));

	for (auto& p : players)
	{
		p.set_players(players);
	}


	int game_state = MENU;
	int current_room = MENU;

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
			updatePlayers(current_screen, players, riddle_triggered, *this);
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
			if (current_screen.get_players_moved() == 2) {
				cls();
				current_room++; // Move to next room index
				auto& next_screen = screens.getgame_screens()[current_room];

				// Check if the next room is the end game screen
				if (current_room == 3) {
					game_state = END_GAME;
					next_screen.draw();
				}
				else {
					// Prepare the next playing room
					prepareNextRoom(next_screen, players);
				}
			}
			setRuntime(); // Update game runtime/cycles
		}
		Sleep(80);
	}
	cls();
}

// Updates player positions, checks for movement triggers
void Game::updatePlayers(Screen& current_screen, vector<Player>& players, bool& riddle_triggered, Game& the_game)
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
		if (p.getIsActive()) {
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
void Game::prepareNextRoom(Screen& next_screen, vector<Player>& players)
{
	next_screen.draw();
	for (auto& p : players) 
	{
		if (p.getIsActive()) 
		{
			// Set player position to room's default coordination and draw it
			p.setPosition(next_screen.getDefault_x(), next_screen.getDefault_y());
			p.setDirection(Direction::STAY);
			p.draw();
		}
	}
	
	
}