#pragma once

enum GameState {
    MENU = 0,
    PLAYING = 1,
    RIDDLE_ACTIVE = 2,
    PAUSED = 3,
    INSTRUCTIONS = 4,
    END_GAME = 5,
    EXIT = 9
};

class Game
{
public:
	enum { MAX_X = 80, MAX_Y = 25 };
};

