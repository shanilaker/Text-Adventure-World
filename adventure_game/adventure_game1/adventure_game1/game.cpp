#include "Game.h"
#include "Screens.h"
#include "Player.h"

void Game::run()
{
	hideCursor();
	Screens screens;
	screens.game_screens[MENU].draw();
	Player players[] = { Player(20, 20, 0, 0, '$',"wdxase", 0, false), Player(10, 10, 0, 0, '&', "ilmjko", 0, false) };

	int game_state = MENU;
	int current_room = MENU;

	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (game_state == MENU)
			{
				if (key == '1')
				{
					cls();
					game_state = PLAYING;
					current_room = 1;
					screens.game_screens[current_room].draw();

				}

				if (key == '9')
				{
					return;
				}

				if (key == '8')
				{
					cls();
					current_room = 4;
					game_state = INSTRUCTIONS;
					screens.game_screens[current_room].draw();


				}
			}

			if (game_state == INSTRUCTIONS)
			{
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.game_screens[MENU].draw();
				}
			}

			if (game_state == END_GAME)
			{
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.game_screens[MENU].draw();
					for (auto& p : players) {
						p.reset();
					}
					for (int i = 1;i < 3;i++)
					{
						screens.game_screens[i].reset();
					}
					
				}
			}

			if (game_state == LOSE)
			{
				cls();
				screens.game_screens[5].draw();
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.game_screens[MENU].draw();
					for (auto& p : players) {
						p.reset();
					}
					for (int i = 1;i < 3;i++)
					{
						screens.game_screens[i].reset();
					}

				}
			}

			if (game_state == RIDDLE_ACTIVE)
			{
				if (key == screens.game_screens[current_room].getScreenRiddle().getAnswer())
				{
					cls();
					screens.game_screens[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							if (p.solvedRiddle == -1)
							{
								p.solvedRiddle = 1;
							}
							if (!p.isWaiting())
							{
								p.draw(' ');
								p.move(screens.game_screens[current_room],*this);
								p.draw();
							}
						}
						

					}
					cout.flush();
				}

				else
				{
					cls();
					screens.game_screens[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							if (p.solvedRiddle == -1)
							{
								p.solvedRiddle = 0;
							}
							p.draw(' ');
							p.draw();
						}
						
					}
					cout.flush();
				}
				game_state = PLAYING;
			}

			else if (game_state == PAUSED) {
				if (key == 'H' || key == 'h') {
					game_state = MENU;
					cls();
					screens.game_screens[MENU].draw();
				}
				else if (key == Keys::ESC) {
					game_state = PLAYING;
					screens.game_screens[PLAYING].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							p.draw();
						}
						
					}
				}
			}
			else if (game_state == PLAYING) {
				if (key == Keys::ESC) {
					// Pause - till any key is pressed
					if (game_state == PLAYING) {
						gotoxy(4, 10);
						cout << "Game paused, press ESC again to continue or H to go back to the main menu";
						game_state = PAUSED;
					}
				}
				else {
					for (auto& p : players) {
						if (p.getIsActive())
						{
							p.handleKeyPressed(key);
						}
						
					}
				}
			}

		}


		if (game_state == PLAYING) {
			bool riddle_triggered = false;

			//GEMINI
			//If the bomb has been activated and the time has come to explode
			if (screens.game_screens[current_room].get_bomb().get_time_to_explode() == run_time && screens.game_screens[current_room].get_bomb().is_bomb_activated())
			{
				//Bomb location
				int bomb_x = screens.game_screens[current_room].get_bomb().getX();
				int bomb_y = screens.game_screens[current_room].get_bomb().getY();
				Screen& current_screen = screens.game_screens[current_room];

				//Erasing the walls - change to only inside the board
				for (int y = bomb_y - 1; y <= bomb_y + 1; y++)
				{
					for (int x = bomb_x - 1; x <= bomb_x + 1; x++)
					{
						/*if (x >= 0 && x < Game::MAX_X && y >= 0 && y < Game::MAX_Y)
						{*/
							char target_char = current_screen.getCharAt(x, y);

							if (target_char == 'W' || target_char == '-' || target_char == '|')
							{
								//Erase
								current_screen.setCharAt(x, y, ' ');
								current_screen.draw(x, y);
							}
						//}
					}
				}

				for (auto& p : players) {

					//Player distance from bomb
					int dist_x = std::abs(p.getX() - bomb_x);
					int dist_y = std::abs(p.getY() - bomb_y);

					int max_dist = max(dist_x, dist_y);

					//Eliminates a player if they are still alive and within 3 yards in any direction.
					if (max_dist <= 3 && p.isActive())
					{
						p.kill();
						game_state = LOSE;
					}
				}

				//Erasing the walls - change to only inside the board
				for (int y = bomb_y - 3; y <= bomb_y + 3; y++)
				{
					for (int x = bomb_x - 3; x <= bomb_x + 3; x++)
					{
						/*if (x >= 0 && x < Game::MAX_X && y >= 0 && y < Game::MAX_Y)
						{*/
						char target_char = current_screen.getCharAt(x, y);

						if (target_char == '?')
						{
							//Erase
							current_screen.getScreenRiddle().kill();
							current_screen.setCharAt(x, y, ' ');
						}
						if (target_char <= '9' && target_char >= '1')
						{
							//Erase
							current_screen.getDoor().kill();
							current_screen.setCharAt(x, y, ' ');
							game_state = LOSE;
						}
						if (target_char == 'K')
						{
							//Erase
							current_screen.setCharAt(x, y, ' ');
							game_state = LOSE;
						}
						if (target_char == '\\' || target_char == '/')
						{
							//Erase
							for (int i = 0; i <= current_screen.getNumSwitches();i++)
							{
								current_screen.getSwitches()[i].kill();
								current_screen.setCharAt(x, y, ' ');
							}
							game_state = LOSE;
						}
						//}
					}
				}

				//Killing the bomb we detonated
				current_screen.get_bomb().kill();
				current_screen.setCharAt(bomb_x, bomb_y, ' ');

				//Draws the new screen and players
				current_screen.draw();

				for (auto& p : players) {
					if (p.getIsActive())
					{
						p.draw();
					}
					
				}
			}


			for (auto& p : players) {
				if (p.getIsActive())
				{
					bool isMoving = (p.getDiffx() != 0 || p.getDiffy() != 0);

					if (!p.isWaiting() && !p.getJustDisposed() && isMoving) {
						p.draw(' ');
					}

					if (p.move(screens.game_screens[current_room], *this)) {
						if (screens.game_screens[current_room].getScreenRiddle().getisActive())
						{
							riddle_triggered = true;
						}
						
					}

					if (!p.isWaiting()) {
						p.draw();
					}
				}

				
			}
			cout.flush();



			if (riddle_triggered) {
				if (screens.game_screens[current_room].getScreenRiddle().getisActive())
				{
					game_state = RIDDLE_ACTIVE;
					screens.game_screens[current_room].getScreenRiddle().Show_Riddle();
				}
				

			}

			if (screens.game_screens[current_room].get_players_moved() == 2)
			{
				cls();
				current_room++;

				if (current_room == 3)
				{
					game_state = END_GAME;
					screens.game_screens[current_room].draw();
				}

				else
				{
					screens.game_screens[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							p.setPosition(screens.game_screens[current_room].getDefault_x(), screens.game_screens[current_room].getDefault_y());
							p.setDirection(Direction::STAY);
							p.draw();
						}
						
					}
				}
			}

			setRuntime();

		}



		Sleep(80);
		
	}
	cls();
}



	

