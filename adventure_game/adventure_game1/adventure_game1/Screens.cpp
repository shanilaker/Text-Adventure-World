#include "Screens.h"
#include <filesystem>


//From tirgul with Amir
void Screens::getAllScreenFileNames(std::vector<std::string>& vec_to_fill)
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 9) == "adv-world" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
	std::sort(vec_to_fill.begin(), vec_to_fill.end());
}

Screens::Screens() {
	int i = 0;
	std::vector<std::string> fileNames;
	getAllScreenFileNames(fileNames);

	if (fileNames.empty()) {
		throw std::runtime_error("No .screen files found in the directory!");
	}

	Riddles riddles_array;

	std::vector<std::string> riddleFileNames;
	riddles_array.getAllRiddleFileNames(riddleFileNames);
	total_riddle_screens_loaded = (int)riddleFileNames.size();

	//Load all the screens
	for (const auto& filename : fileNames)
	{
		game_screens[i].load(filename, i, riddles_array);
		i++;
	}

}

//size_t Screens::getTotalRiddlesCount() {
//	size_t total = 0;
//	for (int i = 0; i < 6; i++) {
//		total += game_screens[i].get_riddles().size();
//	}
//	return total;
//}

size_t Screens::getTotalRiddlesCount() 
{
	size_t total = 0;
	for (int k = 1; k <= 2; k++) 
	{
		for (int i = 0; i < Game::MAX_Y; i++) 
		{
			for (int j = 0; j < Game::MAX_X; j++) 
			{
				if (game_screens[k].getCharAt(j, i) == '?')
				{
					total++;
				}
			}
		}
	}
	return total;
}



