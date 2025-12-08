#include "Bomb.h"
#include "Screen.h"


void Bomb::explodeBomb(Screen& cur_screen, Game& the_game, int& game_state, Player(&players)[2]) {

	if (cur_screen.get_bomb().get_time_to_explode() == the_game.getRuntime() && cur_screen.get_bomb().is_bomb_activated())
	{
		//Bomb location
		int bomb_x = cur_screen.get_bomb().getX();
		int bomb_y = cur_screen.get_bomb().getY();
		Screen& current_screen = cur_screen;

		//Erasing the walls - change to only inside the board
		for (int y = bomb_y - 1; y <= bomb_y + 1; y++)
		{
			for (int x = bomb_x - 1; x <= bomb_x + 1; x++)
			{
				char target_char = current_screen.getCharAt(x, y);

				if (target_char == 'W')
				{
					//Erase
					current_screen.setCharAt(x, y, ' ');
					current_screen.draw(x, y);
				}
				
			}
		}

		for (auto& p : players) {

			//GEMINI HELPED
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
				
			}
		}

		//Killing the bomb we detonated
		current_screen.get_bomb().kill();
		current_screen.setCharAt(bomb_x, bomb_y, ' ');
		current_screen.draw();
	}
}