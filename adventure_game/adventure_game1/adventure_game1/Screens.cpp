#include "Screens.h"


Screens::Screens() {
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
  //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
	  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
	  "W               W                                 W       W                    W", // 1
	  "W               W                                         W                    W", // 2
	  "W      K        ?                                 W       W                    W", // 3    
	  "W               W                                 W       W                    W", // 4
	  "W               W                                 W       W                    W", // 5
	  "WWWWWWWWWWWWWWWWW                                 W       W                    W", // 6
	  "W                                                 W       W     WWWWWWWWWWWWWWWW", // 7
	  "W                                                 W                            W", // 8
	  "W                                                 W                            W", // 9
	  "W                                                 W                            W", // 10
	  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  WWWWWWWWWWWWWWWWWWWWWW", // 11
	  "W                                                 W                            W", // 12
	  "W                                                 W                            W", // 13 
	  "W                                                 W     WWWWWWWWWWWWWWWWWWWWWWWW", // 14
	  "W                                                 W     W                      W", // 15
	  "W                                                 W     W       WWWWWWWWWWWWWWWW", // 16
	  "W                                                 W             W              W", // 17
	  "W                                                 W     W       W              W", // 18
	  "W                                  WWWWWWWWWWWWWWWW     W       W     WWWWW  WWW", // 19
	  "W                                  W              W     W       W     W        W", // 20
	  "W       @                          W       K      W     W       W     W        W", // 21    
	  "W                                  W              W     W             W        W", // 22
	  "W                                                 W     W       W     W       7W", // 23    
	  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" };// 24



	const char* second_room[Game::MAX_Y] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W                  W                    9                      W               W", // 1      
			"W                  W                                           W               W", // 2
			"W                  W                                           W       @       W", // 3    
			"W        \\         W                                           ?               W", // 4    
			"W                  W                                           W               W", // 5
			"W                  W                                           W               W", // 6
			"W                  W                         WWWWWWWWWWWWWWWWWWWWWWWW     WWWWWW", // 7
			"WWWWWWWWWWWWWWWWWWWW                         W                                 W", // 8
			"W                                            W                                 W", // 9
			"W                                            W                                 W", // 10
			"W                                            W                 WWWWWWWWWWWWWWWWW", // 11
			"W                                            W                 W               W", // 12
			"W                                            W              WWWW        \\      W", // 13     
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW              W                  W", // 14
			"W                                                           W                  W", // 15
			"W                                                           W  WWWWWWWWWWWWWWWWW", // 16
			"W                                                     WWWWWWW      W           W", // 17
			"W                                                     W            W    \\      W", // 18      
			"W          W                                          W            W           W", // 19
			"W          WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW           W            W", // 20
			"W                                                             WWWW             W", // 21
			"W          WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                W", // 22
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
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
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
			"--------------------------------------------------------------------------------" };//24

	const char* loser_screen[Game::MAX_Y] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
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
			"--------------------------------------------------------------------------------" };//24
	//Creates the screen array and the relevant screen objects
	Riddles riddles_array;
	Screen menu = Screen(Menu);
	setgame_screens(menu, 0);

	Switch switches1[4] = { Switch(9, 4, false), Switch(72, 13, false), Switch(72, 18, false), Switch(59, 11, false) };

	Switch null_switches[1];

	Screen first_screen = Screen(first_room, riddles_array.getgame_riddles()[0], Door(79, 23, '7', 2, false), 20, 20, Bomb(false, 18, 21, -1), null_switches, 0, 0);
	setgame_screens(first_screen, 1);

	Screen second_screen = Screen(second_room, riddles_array.getgame_riddles()[1], Door(40, 1, '9', 0, true), 1, 23, Bomb(false, 71, 3, -1), switches1, 3, 3);
	setgame_screens(second_screen, 2);

	Screen end_screen = Screen(the_end);
	setgame_screens(end_screen, 3);

	Screen instructions_screen = Screen(Instructions);
	setgame_screens(instructions_screen, 4);

	Screen lose_screen = Screen(loser_screen);
	setgame_screens(lose_screen, 5);
}