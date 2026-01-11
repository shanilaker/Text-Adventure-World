#include "Steps.h"


void Steps::save(const std::string& filename) {
    std::ofstream file(filename);
    file << recorded_steps.size() << "\n";
    for (const auto& s : recorded_steps)
        file << s.iteration << " " << s.key << "\n";
}

void Steps::load(const std::string& filename) {
    std::ifstream file(filename);
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