#include "FileMenager.h"
#include <map>

PlayerData FileMenager::playerData;
ScreenData FileMenager::screenData;
EnemiesData FileMenager::enemiesData;

FileMenager::FileMenager(){
	fileName = nullptr;
}

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

void FileMenager::setDataFromFile() const {
	ifstream file(fileName);
	map<string, float> dataMap;
	string line;

	if (!file.is_open()) {
		cerr << "Error: Could not open file: " << fileName << endl;
		return;
	}

	const regex reg("([a-zA-Z_]+):\\s*(-?\\d*\\.?\\d+)");

	while (getline(file, line)) {
		smatch matches;

		if (regex_search(line, matches, reg)) {
			string key = matches[1].str();
			double value = stof(matches[2].str());
			dataMap[key] = value;
		}
	}

	file.close();

	FileMenager::screenData.size_height = static_cast<unsigned int>(dataMap["screen_size_height"]);
	FileMenager::screenData.size_width = static_cast<unsigned int>(dataMap["screen_size_width"]);

	FileMenager::playerData.size = static_cast<int>(dataMap["player_size"]);
	FileMenager::playerData.start_position_x = dataMap["player_start_position_x"];
	FileMenager::playerData.start_position_y = dataMap["player_start_position_y"];
	FileMenager::playerData.start_position_angle = dataMap["player_start_position_angle"];
	FileMenager::playerData.speed = dataMap["player_speed"];
	FileMenager::playerData.turn_speed = dataMap["player_turn_speed"];
	FileMenager::playerData.bullet_speed = dataMap["player_bullet_speed"];
	FileMenager::playerData.bullet_shoot_delay = dataMap["player_bullet_shoot_delay"];
	FileMenager::playerData.bullet_lifetime = dataMap["player_bullet_lifetime"];
	FileMenager::playerData.bullet_size = static_cast<int>(dataMap["player_bullet_size"]);
	FileMenager::playerData.sprite_cycle_time = dataMap["player_sprite_cycle_time"];
	FileMenager::playerData.dash_duration = dataMap["player_dash_duration"];
	FileMenager::playerData.dash_length = static_cast<int>(dataMap["player_dash_length"]);
	FileMenager::playerData.dash_time_delay = dataMap["player_dash_time_delay"];

	FileMenager::enemiesData.asteroid_spin = dataMap["enemy_asteroid_spin"];
	FileMenager::enemiesData.asteroid_speed = dataMap["enemy_asteroid_speed"];
	FileMenager::enemiesData.asteroid_spawn_time = dataMap["enemy_asteroid_spawn_time"];
	FileMenager::enemiesData.asteroid_size = static_cast<int>(dataMap["enemy_asteroid_size"]);

	return;
}
