#include "Game.h"
#include "Screens.h"
#include "Player.h"

void Game::run()
{
	hideCursor();
	Screens screens;
	screens.getgame_screens()[MENU].draw();
	Player players[] = { Player(20, 20, 0, 0, '$',"wdxase", 0, false), Player(10, 10, 0, 0, '&', "ilmjko", 0, false) };

	int game_state = MENU;
	int current_room = MENU;

	while (true)
	{
		bool riddle_triggered;
		if (_kbhit()) 
		{
			char key = _getch();
			if (game_state == MENU)
			{
				if (key == '1')
				{
					cls();
					game_state = PLAYING;
					current_room = 1;
					screens.getgame_screens()[current_room].draw();

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
					screens.getgame_screens()[current_room].draw();


				}
			}

			if (game_state == INSTRUCTIONS)
			{
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.getgame_screens()[MENU].draw();
				}
			}

			if (game_state == END_GAME)
			{
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.getgame_screens()[MENU].draw();
					for (auto& p : players) {
						p.reset();
					}
					for (int i = 1;i < 3;i++)
					{
						screens.getgame_screens()[i].reset();
					}

				}
			}

			if (game_state == LOSE)
			{
				cls();
				screens.getgame_screens()[5].draw();
				if (key == Keys::ESC)
				{
					game_state = MENU;
					current_room = 0;
					screens.getgame_screens()[MENU].draw();
					for (auto& p : players) {
						p.reset();
					}
					for (int i = 1;i < 3;i++)
					{
						screens.getgame_screens()[i].reset();
					}

				}
			}

			if (game_state == RIDDLE_ACTIVE)
			{
				if (key == screens.getgame_screens()[current_room].getScreenRiddle().getAnswer())
				{
					cls();
					screens.getgame_screens()[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							if (p.getsolvedRiddle() == -1)
							{
								p.setsolvedRiddle(1);
							}
							if (!p.isWaiting())
							{
								p.draw(' ');
								p.move(screens.getgame_screens()[current_room], *this);
								p.draw();
							}
						}


					}
					cout.flush();
				}

				else
				{
					cls();
					screens.getgame_screens()[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							if (p.getsolvedRiddle() == -1)
							{
								p.setsolvedRiddle(0);
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
					current_room = 0;
					screens.getgame_screens()[MENU].draw();
					for (auto& p : players) {
						p.reset();
					}
					for (int i = 1;i < 3;i++)
					{
						screens.getgame_screens()[i].reset();
					}
				}
				else if (key == Keys::ESC) {
					game_state = PLAYING;
					screens.getgame_screens()[PLAYING].draw();
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
			riddle_triggered = false;
			screens.getgame_screens()[current_room].get_bomb().explodeBomb(screens.getgame_screens()[current_room], *this, game_state, players);

				for (auto& p : players) {
					if (p.getIsActive())
					{
						p.draw();
					}

				}
			


			for (auto& p : players) {
				if (p.getIsActive())
				{
					bool isMoving = (p.getDiffx() != 0 || p.getDiffy() != 0);

					if (!p.isWaiting() && !p.getJustDisposed() && isMoving) {
						p.draw(' ');
					}

					if (p.move(screens.getgame_screens()[current_room], *this)) {
						if (screens.getgame_screens()[current_room].getScreenRiddle().getisActive())
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
				if (screens.getgame_screens()[current_room].getScreenRiddle().getisActive())
				{
					game_state = RIDDLE_ACTIVE;
					screens.getgame_screens()[current_room].getScreenRiddle().Show_Riddle();
				}
				

			}

			if (screens.getgame_screens()[current_room].get_players_moved() == 2)
			{
				cls();
				current_room++;

				if (current_room == 3)
				{
					game_state = END_GAME;
					screens.getgame_screens()[current_room].draw();
				}

				else
				{
					screens.getgame_screens()[current_room].draw();
					for (auto& p : players) {
						if (p.getIsActive())
						{
							p.setPosition(screens.getgame_screens()[current_room].getDefault_x(), screens.getgame_screens()[current_room].getDefault_y());
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



	

