#include "Bomb.h"
#include "Screen.h"

void Bomb::explodeBomb(Screen& cur_screen, Game& the_game, int& game_state, vector<Player>& players)
{
	if (x < 0 || y < 0 || !is_activated) return;

	if (time_to_explode == the_game.getRuntime() && is_activated)
	{
		//Bomb location
		int bomb_x = x;
		int bomb_y = y;
		Screen& current_screen = cur_screen;
	
		//Erasing the walls - change to only inside the board
		for (int y_ = bomb_y - 1; y_ <= bomb_y + 1; y_++)
		{
			for (int x_ = bomb_x - 1; x_ <= bomb_x + 1; x_++)
			{
				char target_char = current_screen.getCharAt(x_, y_);
	
				if (target_char == Object::WALL)
				{
					//Erase
					current_screen.setCharAt(x_, y_, Object::SPACE);
					current_screen.draw(x_, y_);
				}
	
			}
		}
	
		for (auto& p : players) 
		{
			p.checkAndkill(bomb_x, bomb_y, game_state, the_game);
			cur_screen.get_screen_legend().update_values(p, cur_screen);
		}
	
		//Erasing the walls - change to only inside the board
		for (int y_ = bomb_y - 3; y_ <= bomb_y + 3; y_++)
		{
			for (int x_ = bomb_x - 3; x_ <= bomb_x + 3; x_++)
			{
				char target_char = current_screen.getCharAt(x_, y_);
	
				if (target_char == Object::RIDDLE)
				{
					//Erase
					for (auto& riddle : current_screen.get_riddles())
					{
						if(x_ == riddle.getX() && y_ == riddle.getY())
							riddle.kill();
					}
					current_screen.setCharAt(x_, y_, Object::SPACE);
				}
				if (target_char <= '9' && target_char >= '1')
				{
					//Erase
					current_screen.getDoor(target_char).kill();
					current_screen.setCharAt(x_, y_, Object::SPACE);
					game_state = LOSE;
					if (auto* humanGame = dynamic_cast<HumanInputGame*>(&the_game)) {
						humanGame->SaveGame();
					}
					if (!the_game.shouldShowMenu())
						game_state = EXIT;
				}
				if (target_char == Object::KEY)
				{
					//Erase
					current_screen.setCharAt(x_, y_, Object::SPACE);
					game_state = LOSE;
					if (auto* humanGame = dynamic_cast<HumanInputGame*>(&the_game)) {
						humanGame->SaveGame();
					}
					if (!the_game.shouldShowMenu())
						game_state = EXIT;
				}
				if (target_char == Object::C_SWITCH || target_char == Object::O_SWITCH)
				{
					//Erase
					for (int i = 0; i < current_screen.getNumSwitches() ;i++)
					{
						current_screen.getSwitches()[i].kill();
						current_screen.setCharAt(x_, y_, Object::SPACE);
					}
					game_state = LOSE;
					if (auto* humanGame = dynamic_cast<HumanInputGame*>(&the_game)) {
						humanGame->SaveGame();
					}
					if (!the_game.shouldShowMenu())
						game_state = EXIT;
				}
	
			}
		}
	
		//Killing the bomb we detonated
		this->kill(current_screen, bomb_x, bomb_y);
	
	}
	
}

void Bomb::kill(Screen & current_screen, const int& bomb_x, const int& bomb_y) {
	is_active = false;
	current_screen.setCharAt(bomb_x, bomb_y, Object::SPACE);
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

void Bomb::reset() 
{
	is_active = true;
	is_activated = false;
	x = r_x;
	y = r_y;
	set_time_to_explode(-6);
}

	