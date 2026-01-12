#include "Game.h"

FileInputGame::FileInputGame(bool silent) : is_silent_mode(silent) {
    Game::silent_mode = silent;
    stepsLibrary.load("adv-world.steps");
    resultsCheck.load("adv-world.result");
}

void FileInputGame::recordEvent(GameEvent type, int data) {
    // If the file doesn't even have an event at this timestamp, it's an unexpected event
    if (!resultsCheck.hasEventAtTime(run_time)) {
        handleMismatch(type, run_time, "UNEXPECTED EVENT - This event did not happen in the original game", data, -1);
        return;
    }

    // Get the file data to compare with current data
    EventRecord expected = resultsCheck.getNextExpectedEvent();

    // Compare type and data. If they don't match, trigger a failure
    if (!resultsCheck.validateEvent(run_time, type, data)) {
        handleMismatch((GameEvent)expected.eventType, expected.iteration, "DATA MISMATCH - The event details are different from the original game", expected.data, data, type);
    }
}

void FileInputGame::checkValidation(int current_iter) {
    if (resultsCheck.hasMissedEvent(current_iter)) {
        EventRecord missed = resultsCheck.getNextExpectedEvent();
        handleMismatch((GameEvent)missed.eventType, missed.iteration, "MISSED EVENT ERROR - An event was expected but never triggered", missed.data, -1);
    }
}


std::string FileInputGame::getEventName(GameEvent type) const {
    switch (type) {
    case CHANGE_ROOM:
        return "CHANGE_ROOM";
    case LIFE_LOST:
        return "LIFE_LOST";
    case RIDDLE_START:
        return "RIDDLE_START";
    case RIDDLE_ANSWER:
        return "RIDDLE_ANSWER";
    case RIDDLE_RESULT:
        return "RIDDLE_RESULT";
    case GAME_FINISHED:
        return "GAME_FINISHED";
    default:
        return "UNKNOWN_EVENT";
    }
}

std::string FileInputGame::formatEventData(GameEvent type, int data) const {
    if (data == -1) return "N/A";
    switch (type) {
    case LIFE_LOST:
    case RIDDLE_START:
        return std::string("Player '") + (char)data + "'";
    case RIDDLE_ANSWER:
        return std::string("Key pressed: '") + (char)data + "'";
    case CHANGE_ROOM:
        return "Room " + std::to_string(data);
    case RIDDLE_RESULT:
        return (data == 1) ? "Correct Answer" : "Wrong Answer";
    case GAME_FINISHED:
        return "Final Score: " + std::to_string(data);
    default:
        return std::to_string(data);
    }
}

void FileInputGame::handleMismatch(GameEvent expectedType, int expectedTime, const std::string & errorMsg, int expectedData, int actualData, GameEvent actualType)
{
    cls();
    std::cout << "==================================================" << std::endl;
    std::cout << "             REPLAY VALIDATION ERROR              " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << errorMsg << std::endl;
    std::cout << "Current Iteration: " << run_time << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    std::cout << "EXPECTED (from file):" << std::endl;
    std::cout << "  Type: " << getEventName(expectedType) << std::endl;
    std::cout << "  Info: " << formatEventData(expectedType, expectedData) << std::endl;
    std::cout << "  Time: " << expectedTime << std::endl;

    if (actualType != -1) {
        std::cout << "\nACTUAL (in current run):" << std::endl;
        std::cout << "  Type: " << getEventName(actualType) << std::endl;
        std::cout << "  Info: " << formatEventData(actualType, actualData) << std::endl;
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Press any key to exit replay..." << std::endl;
    (void)_getch();
    validation_failed = true;
    game_state = EXIT;
}

void FileInputGame::validateScreens(const std::vector<std::string>& current_screens) {
    if (current_screens != stepsLibrary.getScreenFiles()) {
        cls();
        std::cout << "====================================================" << std::endl;
        std::cout << "           CRITICAL ERROR: SCREEN MISMATCH          " << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << "The recording was created with different screen files." << std::endl;
        std::cout << "\nRECORDED: ";
        for (auto& s : stepsLibrary.getScreenFiles()) std::cout << s << " ";
        std::cout << "\nCURRENT:  ";
        for (auto& s : current_screens) std::cout << s << " ";
        std::cout << "\n\nPress any key to exit..." << std::endl;
        (void)_getch();
        validation_failed = true;
        game_state = EXIT;
    }
}