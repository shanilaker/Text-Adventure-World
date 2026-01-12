#pragma once
#include <vector>
#include <string>
#include <fstream>

struct Step {
    int iteration;
    char key;
};

class Steps {
    std::vector<Step> recorded_steps;
    std::vector<std::string> screen_filenames;
public:
    // Saves a single key pressed and the time (iteration) it occurred
    void addStep(int iter, char k) { recorded_steps.push_back({ iter, k }); }

    // Saves all user key presses to a file named "adv-world.steps"
    void save(const std::string& filename);

    // Loads all key presses from a file for replay mode
    void load(const std::string& filename);
    
    // Gets and removes the key pressed for the current iteration, if any exists
    char popNextKey(int current_iter);

    // Save screen file names
    void setScreenFiles(const std::vector<std::string>& files) { screen_filenames = files; }

    // Get the screen file names
    const std::vector<std::string>& getScreenFiles() const { return screen_filenames; }
};

