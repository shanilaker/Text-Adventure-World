#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Screens.h"
#include "Player.h"

enum Keys { ESC = 27 };

int main() {
	hideCursor();
	Screens screens;
	screens.game_screens[0].draw();
	Player players[] = { Player(20, 30, 1, 0, '@',"wdxas"), Player(10, 10, 1, 0, '#', "ilmjk") };
	int game_state = 0;
	
	while (true) {
		if (_kbhit()) {
			char start_key = _getch();
			if (start_key == '1')
			{
				cls();
				screens.game_screens[1].draw();
				game_state = 1;
			}
		}
		if (_kbhit()) {
			char key = _getch();
			
			if (key == Keys::ESC) {
				// add a note  “Game paused, press ESC again to continue or X to go back to the main menu”.
				// Pause - till any key is pressed
				key = _getch();
				if (key == 'H' || key == 'h') {
					//go to menu
				}
				if (key == Keys::ESC) {
					break;
				}
			}
			else {
				for (auto& p : players) {
					p.handleKeyPressed(key);
					
				}
			}
		}

		if (game_state == 1) {
			for (auto& p : players) {
				p.draw(' ');
				p.move();
				p.draw();
			}
			cout.flush(); 
		}

		Sleep(50);
	}
	cls();
}