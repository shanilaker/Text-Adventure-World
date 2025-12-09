#pragma once
#include "Game.h"
#include "Screens.h"
#include "Player.h"
#include <conio.h>

class Menu {
    Screens& screens;
public:
    Menu(Screens& s);

    GameState run(GameState current_state, int& current_room_id, Player(&players)[2], char key);
};

