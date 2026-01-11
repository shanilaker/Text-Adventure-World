#include "Game.h"


HumanInputGame::~HumanInputGame() {
    if (is_save_mode) {
        stepsTracker.save("adv-world.steps");
        resultsTracker.save("adv-world.result");
    }
}

void HumanInputGame::recordEvent(GameEvent type, int data) {
    if (is_save_mode)
        resultsTracker.addEvent(run_time, type, data);
}

char HumanInputGame::getInput() {
    if (_kbhit()) {
        char key = (char)_getch();
        if (is_save_mode)
            stepsTracker.addStep(run_time, key);
        return key;
    }
    return '\0';
}

void HumanInputGame::SaveGame() {
    if (is_save_mode) {
        stepsTracker.save("adv-world.steps");
        resultsTracker.save("adv-world.result");
    }
}
