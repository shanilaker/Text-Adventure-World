#pragma once
#include "Screen.h"
#include "Riddles.h"
#include "Bomb.h"
#include "Game.h"

class Screens
{
public:
	Screen game_screens[6];
	Screens() {
		const char* Menu[Game::MAX_Y] = {
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				"********************************************************************************", // 0
				"*. . * . . . * . . * * . . * . * . * . . . * * . * . . * . * . . * . . . * . * *", // 1
				"* . * . . . * . * . . . * . . * . . * . * . . . * . * . . . * . * . * . . . *  *", // 2
				"*. * . . . * . * . . . * . . * . . * . * . . . * . * . . . * . * . * . . . * . *", // 3
				"*. * . . . * . * . . . * . . * . . * . * . . . * . * . . . * . * . * . . . * . *", // 4
				"* . . * . * . . * . . . * . * . * . . . * * . * . . * . * . . * . . . * . * .  *", // 5
				"********************************************************************************", // 6
				"|                                                                              |", // 7
				"|                     - - -     LET THE GAMES BEGIN   - - -                    |", // 8
				"|                     =====================================                    |", // 9
				"|                                                                              |", // 10
				"|                                                                              |", // 11
				"|                             (1) Start a new game                             |", // 12
				"|                                                                              |", // 13
				"|                       (8) Present instructions and keys                      |", // 14
				"|                                                                              |", // 15
				"|                                    (9) EXIT                                  |", // 16
				"|                                                                              |", // 17
				"|                                                                              |", // 18
				"|                                                                              |", // 19
				"|==============================================================================|", // 20
				"| ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~~ |", // 21
				"| ~~~~~~~~~~ ~~~~~~~~~ ~~~~~~~~ ~~~~~~~~ ~~~~~~~~ ~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~ |", // 22
				"| ~~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~ ~~~~~~~~~~ |", // 23
				"|==============================================================================|" };// 24

		const char* first_room[Game::MAX_Y] = {
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
				"|                                                                              W", // 1
				"|                                                                              W", // 2
				"|            @                                               ?                 W", // 3
				"|                                                                              W", // 4
				"|                                                                              W", // 5
				"|                                 .---------.                                  W", // 6
				"|                                 |         |                                  W", // 7
				"|                                 |         |                                  W", // 8
				"|                                 |  [OFF]  |                                  W", // 9
				"|                                 |         |                                  W", // 10
				"|                                 '---------'                                  W", // 11
				"|                                                                              W", // 12
				"|                                                                         K    W", // 13 
				"|                                                                              W", // 14
				"|                                                                              W", // 15
				"|                                                                              W", // 16
				"|                                                                              W", // 17
				"|            K                                                                 W", // 18
				"|                                                                              W", // 19
				"|                                                                              W", // 20
				"|                                                                              W", // 21
				"|                                                                              W", // 22
				"|                                                                             7W", // 23
				"-------------------------------------------------------------------------------W" };// 24


		const char* second_room[Game::MAX_Y] = {
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
				  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
				  "W9                                                                             W", // 1
				  "W                                                                              W", // 2
				  "W                                                                             ?W", // 3
				  "W                                                                              W", // 4
				  "W          @                                                                   W", // 5
				  "W                              .---------.                                     W", // 6
				  "W                              |         |                                     W", // 7
				  "W                              |         |                                     W", // 8
				  "W                              |  [OFF]  |                                     W", // 9
				  "W                              |         |                 \\ \\                 W", // 10
				  "W                              '---------'                 \\ \\                 W", // 11
				  "W                                                                              W", // 12
				  "W                                                                         K    W", // 13 
				  "W                                                                              W", // 14
				  "W                                                                              W", // 15
				  "W                                                                              W", // 16
				  "W                                                                              W", // 17
				  "W               K                                                              W", // 18
				  "W                                                                              W", // 19
				  "W                                                                              W", // 20
				  "W                                                                              W", // 21
				  "W                      K                                                       W", // 22
				  "W                                                                              W", // 23
				  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" };// 24
		const char* Instructions[Game::MAX_Y] = {
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	"--------------------------------------------------------------------------------", // 0
	"|  *PRESS ESC TO EXIT           GAME INSTRUCTIONS                              |", // 1
	"|------------------------------------------------------------------------------|", // 2
	"| Movement Keys:                                                               |", // 3
	"|                                                                              |", // 4
	"|    Player 1:         Player 2:                                               |", // 5
	"|     W  Up              I  Up                                                 |", // 6
	"|     A  Left            J  Left                                               |", // 7
	"|     S  Stay            K  Stay                                               |", // 8
	"|     D  Right           L  Right                                              |", // 9
	"|     X  Down            M  Down                                               |", // 10
	"|     E  Drop item       O  Drop Item                                          |", // 11
	"|                                                                              |", // 12
	"|------------------------------------------------------------------------------|", // 13 
	"|                                                                              |", // 14
	"|  Game Elements:                                                              |", // 15
	"|                                                                              |", // 16
	"|   # Spring - compress it to gain speed when released.                        |", // 17
	"|   K Key - collect to open matching doors.                                    |", // 18
	"|   1-9 Door - step on it to move to another room (if allowed).                |", // 19
	"|   ? Riddle - solve it to pass through                                        |", // 20
	"|   W Wall - blocks movement                                                   |", // 21
	"|                                                                              |", // 22
	"| The two players must cooperate to solver each room and reach the final room. |", // 23
	"--------------------------------------------------------------------------------" };// 24
		

		const char* the_end[Game::MAX_Y] = {
	"--------------------------------------------------------------------------------", // 0
	"|                                                                              |", // 1
	"|                                                                              |", // 2
	"|                                                                              |", // 3
	"|                                                                              |", // 4
	"|                                                                              |", // 5
	"|                            ************************                          |", // 6
	"|                            *   CONGRATULATIONS!   *                          |", // 7
	"|                            ************************                          |", // 8
	"|                                                                              |", // 9
	"|                            You have completed the game!                      |", // 10
	"|                                                                              |", // 11
	"|                      Thank you for playing the Adventure World               |", // 12
	"|                                                                              |", // 13
	"|                            Press ESC to return to menu                       |", // 14
	"|                                                                              |", // 15
	"|                                                                              |", // 16
	"|                                                                              |", // 17
	"|                                                                              |", // 18
	"|                                                                              |", // 19
	"|                                                                              |", // 20
	"|                                                                              |", // 21
	"|                                                                              |", // 22
	"|                                                                              |", // 23
	"--------------------------------------------------------------------------------"  // 24
		};

		const char* loser_screen[Game::MAX_Y] = {
	"--------------------------------------------------------------------------------", // 0
	"|                                                                              |", // 1
	"|                                                                              |", // 2
	"|                                                                              |", // 3
	"|                                                                              |", // 4
	"|                                                                              |", // 5
	"|                            ************************                          |", // 6
	"|                            *       YOU LOST :(    *                          |", // 7
	"|                            ************************                          |", // 8
	"|                                                                              |", // 9
	"|                      You are out of options to solve the room,               |", // 10
	"|                                                                              |", // 11
	"|                      Thank you for playing the Adventure World               |", // 12
	"|                                                                              |", // 13
	"|                            Press ESC to return to menu                       |", // 14
	"|                                                                              |", // 15
	"|                                                                              |", // 16
	"|                                                                              |", // 17
	"|                                                                              |", // 18
	"|                                                                              |", // 19
	"|                                                                              |", // 20
	"|                                                                              |", // 21
	"|                                                                              |", // 22
	"|                                                                              |", // 23
	"--------------------------------------------------------------------------------"  // 24
		};

		Riddles riddles_array;
		Screen menu = Screen(Menu);
		game_screens[0] = menu;

		Switch switches1[4] = {
	  Switch(61, 10, false),
	  Switch(59, 10, false),
	  Switch(61, 11, false),
	  Switch(59, 11, false) };

		Switch null_switches[1];

		Screen first_screen = Screen(first_room, riddles_array.game_riddles[0], Door(79, 23, '7', 2, false), 20, 20, Bomb(false, 13, 3,-1), null_switches, 0, 0);
		game_screens[1] = first_screen;

		Screen second_screen = Screen(second_room, riddles_array.game_riddles[1], Door(1, 1, '9', 0, true), 1, 23, Bomb(false, 11, 5,-1), switches1, 4, 4);
		game_screens[2] = second_screen;

		Screen lose_screen = Screen(loser_screen);
		game_screens[5] = lose_screen;

		Screen end_screen = Screen(the_end);
		game_screens[3] = end_screen;

		Screen instructions_screen = Screen(Instructions);
		game_screens[4] = instructions_screen;
	}
};

