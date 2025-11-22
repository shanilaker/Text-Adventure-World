#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Screens.h"

enum Keys { ESC = 27 };

int main() {
	//hideCursor();
	Screens screens;
	screens.game_screens[0].draw();
	//Player players[] = { Player player1(10, 10, 1, 0, '@'), Player player2(10, 10, 1, 0, '@') };

	
	while (true) {
		
		if (_kbhit()) {
			char start_key = _getch();
			if (start_key == '1')
			{
				cls();
				//screen.draw();
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
			/*else {
				for (auto& p : players) {
					p.handleKeyPressed(key);
				}
			}*/
		}
		Sleep(50);
	}
	cls();
}