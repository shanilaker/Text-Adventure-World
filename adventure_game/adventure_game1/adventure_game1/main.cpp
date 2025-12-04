#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Screens.h"
#include "Player.h"
#include "Game.h"

enum Keys { ESC = 27 };

int main() {
	hideCursor();
	Screens screens;
	screens.game_screens[MENU].draw();
	Player players[] = { Player(20, 20, 0, 0, '@',"wdxase", 0, false), Player(10, 10, 0, 0, '#', "ilmjko", 0, false) };

	int game_state = MENU;
	int current_room = MENU;

	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (game_state == MENU && key == '1')
			{
				cls();
				game_state = PLAYING;
				current_room = 1;
				screens.game_screens[current_room].draw();

			}
			if (game_state == RIDDLE_ACTIVE)
			{
				if (key == screens.game_screens[current_room].getScreenRiddle().getAnswer())
				{
					cls();
					screens.game_screens[current_room].draw();
					for (auto& p : players) {
						if (p.solvedRiddle == -1)
						{
							p.solvedRiddle = 1;
						}
						p.draw(' ');
						p.move(screens.game_screens[current_room]);
						p.draw();
					}
					cout.flush();
				}
				
				else
				{
					cls();
					screens.game_screens[current_room].draw();
					for (auto& p : players) {
						if (p.solvedRiddle == -1)
						{
							p.solvedRiddle = 0;
						}
						p.draw(' ');
						p.draw();
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
						p.draw();
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
						p.handleKeyPressed(key);
					}
				}
			}

		}


			if (game_state == PLAYING) {
				bool riddle_triggered = false;

				for (auto& p : players) {

					if (!p.isWaiting()) {
						p.draw(' ');
					}

					if (p.move(screens.game_screens[current_room])) {
						riddle_triggered = true;
					}

					if (!p.isWaiting()) {
						p.draw();
					}
				}
				cout.flush();

				

				if (riddle_triggered) {
					game_state = RIDDLE_ACTIVE;
					screens.game_screens[current_room].getScreenRiddle().draw();

				}

				if (screens.game_screens[current_room].get_players_moved() == 2)
				{
					cls();
					current_room++;
					screens.game_screens[current_room].draw();
					/*for (auto& p : players) {
						p.setPosition(screens.game_screens[current_room].getDefault_x(), screens.game_screens[current_room].getDefault_y());
					}*/
					
				}
			}

			
		
		Sleep(50);
		
	}
	cls();
	return 0;
}
