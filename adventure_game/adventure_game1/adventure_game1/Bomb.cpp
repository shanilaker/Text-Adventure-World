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
		for (int y_ = bomb_y - 1; y_ <= bomb_y + 1; y_++)
		{
			for (int x_ = bomb_x - 1; x_ <= bomb_x + 1; x_++)
			{
				char target_char = current_screen.getCharAt(x_, y_);

				if (target_char == 'W')
				{
					//Erase
					current_screen.setCharAt(x_, y_, ' ');
					current_screen.draw(x_, y_);
				}
				
			}
		}

		for (auto& p : players) {

			p.checkAndkill(bomb_x, bomb_y, game_state);
		}

		//Erasing the walls - change to only inside the board
		for (int y_ = bomb_y - 3; y_ <= bomb_y + 3; y_++)
		{
			for (int x_ = bomb_x - 3; x_ <= bomb_x + 3; x_++)
			{
				char target_char = current_screen.getCharAt(x_, y_);

				if (target_char == '?')
				{
					//Erase
					current_screen.getScreenRiddle().kill();
					current_screen.setCharAt(x_, y_, ' ');
				}
				if (target_char <= '9' && target_char >= '1')
				{
					//Erase
					current_screen.getDoor().kill();
					current_screen.setCharAt(x_, y_, ' ');
					game_state = LOSE;
				}
				if (target_char == 'K')
				{
					//Erase
					current_screen.setCharAt(x_, y_, ' ');
					game_state = LOSE;
				}
				if (target_char == '\\' || target_char == '/')
				{
					//Erase
					for (int i = 0; i <= current_screen.getNumSwitches();i++)
					{
						current_screen.getSwitches()[i].kill();
						current_screen.setCharAt(x_, y_, ' ');
					}
					game_state = LOSE;
				}
				
			}
		}

		//Killing the bomb we detonated
		current_screen.get_bomb().kill(current_screen,bomb_x,bomb_y);

	}
}

	void Bomb::kill(Screen & current_screen, const int& bomb_x, const int& bomb_y) {
		is_active = false;
		current_screen.setCharAt(bomb_x, bomb_y, ' ');
		current_screen.draw();
	}

	void Bomb::set_is_activated(const bool& set_to, const int& x1, const int& y1) {
		is_activated = set_to;
		if (set_to)
		{
			is_activated = true;
			x = x1;
			y = y1;
		}

	}