#include "Steps.h"


void Steps::save(const std::string& filename) {
    std::ofstream file(filename);
    // save filenames
    file << screen_filenames.size() << "\n";
    for (const auto& name : screen_filenames)
        file << name << "\n";

    // save steps
    file << recorded_steps.size() << "\n";
    for (const auto& s : recorded_steps)
        file << s.iteration << " " << s.key << "\n";
}



void Steps::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    size_t screen_count = 0;
    if (!(file >> screen_count)) return;

    screen_filenames.clear();
    for (size_t i = 0; i < screen_count; ++i) {
        std::string name;
        file >> std::ws;
        if (!(file >> name)) break;
        screen_filenames.push_back(name);
    }

    size_t size;
    if (!(file >> size)) return;
    recorded_steps.resize(size);
    for (size_t i = 0; i < size; ++i)
        file >> recorded_steps[i].iteration >> recorded_steps[i].key;
}

char Steps::popNextKey(int current_iter) {
    if (!recorded_steps.empty() && recorded_steps.front().iteration == current_iter) {
        char k = recorded_steps.front().key;
        recorded_steps.erase(recorded_steps.begin()); // remove used step
        return k;
    }
    return '\0';
}