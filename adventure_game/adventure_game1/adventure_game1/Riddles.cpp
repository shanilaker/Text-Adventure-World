#include "Riddles.h"
#include "Game.h"
#include <filesystem>


//From tirgul with Amir
void Riddles::getAllRiddleFileNames(std::vector<std::string>& vec_to_fill)
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "riddle" && filename.extension() == ".riddle") {
			vec_to_fill.push_back(filenameStr);
		}
	}
	std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

Riddles::Riddles()
{
	//Update the riddles from a file
	std::vector<std::string> fileNames;
	getAllRiddleFileNames(fileNames);
	for (const auto& filename : fileNames)
	{
		Riddle r;       
		r.load(filename); 
		game_riddles.push_back(r);
	}

}
