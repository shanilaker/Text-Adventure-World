#pragma once
#include <vector>
#include <string>
#include <fstream>

enum GameEvent {    
    CHANGE_ROOM = 1, 
    LIFE_LOST = 2,   
    RIDDLE_START = 3,
    RIDDLE_ANSWER = 4,
    RIDDLE_RESULT = 5,
    GAME_FINISHED = 6
};

struct EventRecord {
    int iteration;
    int eventType;
    int data; 
};

class Results {
    std::vector<EventRecord> events;

public:
    // Adds an event (e.g., life lost, room change) to the record buffer
    void addEvent(int iter, GameEvent type, int data = 0) { events.push_back({ iter, (int)type, data }); }
    
    // Saves all events to a file named "adv-world.result"
    void save(const std::string& filename);

    // Loads events from a result file for validation during replay
    void load(const std::string& filename);
    
    // Validates if the current game event matches the next expected event in the loaded game
    bool validateEvent(int iter, GameEvent type, int data);
    
    // Checks if an event from the file was supposed to happen at a time that has already passed
    bool hasMissedEvent(int current_iter) const;

    // Gets the next expected event from the top of the loaded events list
    EventRecord getNextExpectedEvent() const;

    // Returns true if the next event in the file is happening in the current iteration
    bool hasEventAtTime(int current_iter) const { return (!events.empty() && events.front().iteration == current_iter);}
};