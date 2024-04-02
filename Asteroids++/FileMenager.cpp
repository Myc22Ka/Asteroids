#include "FileMenager.h"
#include <map>

PlayerData FileMenager::playerData;
ScreenData FileMenager::screenData;

FileMenager::FileMenager() {}

FileMenager::~FileMenager()
{
	delete[] fileName;
}

void FileMenager::setFileName(const char* name)
{
	delete[] fileName;

	size_t length = strlen(name);
	fileName = new char[length + 1];
	strcpy_s(fileName, length + 1, name);
}

const char* FileMenager::getFileName() const
{
	return fileName;
}

void FileMenager::setDataFromFile() {
	std::ifstream file(fileName);
	std::map<std::string, float> dataMap;
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file: " << fileName << std::endl;
		return;
	}

	const std::regex reg("([a-zA-Z_]+):\\s*(-?\\d*\\.?\\d+)");

	while (std::getline(file, line)) {
		std::smatch matches;

		if (std::regex_search(line, matches, reg)) {
			std::string key = matches[1].str();
			double value = std::stof(matches[2].str());
			dataMap[key] = value;
		}
	}

	file.close();

	FileMenager::screenData.size_height = dataMap["screen_size_height"];
	FileMenager::screenData.size_width = dataMap["screen_size_width"];

	FileMenager::playerData.size = dataMap["player_size"];
	FileMenager::playerData.start_position_x = dataMap["player_start_position_x"];
	FileMenager::playerData.start_position_y = dataMap["player_start_position_y"];
	FileMenager::playerData.start_position_angle = dataMap["player_start_position_angle"];
	FileMenager::playerData.speed = dataMap["player_speed"];
	FileMenager::playerData.turn_speed = dataMap["player_turn_speed"];
	FileMenager::playerData.bullet_speed = dataMap["player_bullet_speed"];
	FileMenager::playerData.bullet_shoot_delay = dataMap["player_bullet_shoot_delay"];
	FileMenager::playerData.bullet_lifetime = dataMap["player_bullet_lifetime"];

	return;
}
