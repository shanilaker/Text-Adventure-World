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
	Player players[] = { Player(20, 20, 0, 0, '$',"wdxase", 0, false), Player(10, 10, 0, 0, '&', "ilmjko", 0, false) };

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
				current_screen.getScreenRiddle().checkRiddleAnswer(current_screen, *this, key, players);
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
			current_screen.get_bomb().explodeBomb(current_screen, *this, game_state, players);
			// Update player positions, movement and check for triggers
			updatePlayers(current_screen, players, riddle_triggered, *this);
			cout.flush();

			// Handle riddle trigger event
			if (riddle_triggered) {
				if (current_screen.getScreenRiddle().getisActive()) {
					game_state = RIDDLE_ACTIVE;
					current_screen.getScreenRiddle().Show_Riddle();
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
void Game::updatePlayers(Screen& current_screen, Player(&players)[2], bool& riddle_triggered, Game& the_game) {
	for (auto& p : players) {
		if (p.getIsActive()) {
			// Clear player's previous position
			if (!p.isWaiting() && !p.getJustDisposed()) {
				p.draw(' ');
			}
			// Move the player
			if (p.move(current_screen, the_game)) {
				if (current_screen.getScreenRiddle().getisActive()) {
					riddle_triggered = true;
				}
			}
			// Draw the player in new position
			if (!p.isWaiting()) {
				p.draw();
			}
		}
	}
}
// Prepares next screen and player positions for it 
void Game::prepareNextRoom(Screen& next_screen, Player(&players)[2]) {
	next_screen.draw();
	for (auto& p : players) {
		if (p.getIsActive()) {
			// Set player position to room's default coordination and draw it
			p.setPosition(next_screen.getDefault_x(), next_screen.getDefault_y());
			p.setDirection(Direction::STAY);
			p.draw();
		}
	}
}