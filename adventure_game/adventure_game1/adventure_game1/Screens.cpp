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
	Riddles riddles_array;

	//Load all the screens
	for (const auto& filename : fileNames)
	{
		game_screens[i].load(filename, i, riddles_array);
		i++;
	}

}

size_t Screens::getTotalRiddlesCount() {
	size_t total = 0;
	for (int i = 0; i < 6; i++) {
		total += game_screens[i].get_riddles().size();
	}
	return total;
}


