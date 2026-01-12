#include "Results.h"


void Results::save(const std::string& filename) {
    std::ofstream file(filename);
    file << events.size() << "\n";
    for (const auto& e : events)
        file << e.iteration << " " << e.eventType << " " << e.data << "\n";
}

void Results::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    size_t size;
    if (!(file >> size)) return;
    events.clear();
    for (size_t i = 0; i < size; ++i) {
        int iter, type, data;
        if (!(file >> iter >> type >> data)) break; 
        events.push_back({ iter, type, data });
    }
}

bool Results::validateEvent(int iter, GameEvent type, int data) {
    if (events.empty() || events.front().iteration != iter || events.front().eventType != (int)type) {
        return false;
    }
    bool match = (events.front().data == data);
    events.erase(events.begin());
    return match;
}

bool Results::hasMissedEvent(int current_iter) const {
    if (!events.empty() && events.front().iteration <= current_iter) {
        return true;
    }
    return false;
}

EventRecord Results::getNextExpectedEvent() const {
    if (!events.empty()) {
        return events.front();
    }
    return { -1, -1, -1 };
}