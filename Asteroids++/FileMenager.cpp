#include "FileMenager.h"
#include <map>

PlayerData FileMenager::playerData;
ScreenData FileMenager::screenData;
EnemiesData FileMenager::enemiesData;
DrawsData FileMenager::drawsData;
TimingsData FileMenager::timingsData;
vector<pair<string, float>> FileMenager::highScore;

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

vector<pair<string, float>> FileMenager::sortMapByFloat(const map<string, float>& inputMap) {
	vector<pair<string, float>> pairs;

	for (const auto& pair : inputMap) {
		pairs.push_back(pair);
	}

	// Sort the vector using the sortByFloatValue comparator function
	sort(pairs.begin(), pairs.end(), sortByFloatValue);

	return pairs;
}

bool FileMenager::sortByFloatValue(const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
	return a.second > b.second;
}

void FileMenager::saveData(const string& fileName, const pair<string, int>& data) {
	ifstream checkFile(fileName);

	if (!checkFile) {
		ofstream file(fileName);

		if (!file.is_open()) {
			cerr << "Error: Could not create file: " << fileName << endl;
			return;
		}

		file << "# HighScore" << endl;
		file << data.first << ": " << data.second << endl;
		file.close();
	}
	else {
		ofstream file(fileName, ios::app);

		if (!file.is_open()) {
			cerr << "Error: Could not open file for appending: " << fileName << endl;
			return;
		}

		file << data.first << ": " << data.second << endl;
	}
}
map<string, float> FileMenager::getDataFromFile(const string& name){
	ifstream file(name);
	map<string, float> dataMap;
	string line;

	if (!file.is_open()) {
		cerr << "Error: Could not open file: " << name << endl;
		return dataMap;
	}

	const regex reg("([a-zA-Z_]+):\\s*(-?\\d*\\.?\\d+)");

	while (getline(file, line)) {
		smatch matches;

		if (regex_search(line, matches, reg)) {
			string key = matches[1].str();
			float value = stof(matches[2].str());
			dataMap[key] = value;
		}
	}

	file.close();

	return dataMap;
}

void FileMenager::setDataFromFile() const {
	auto dataMap = getDataFromFile(fileName);

	screenData.padding = dataMap["screen_padding"];
	screenData.framerate = static_cast<int>(dataMap["framerate"]);
	screenData.launch_time = dataMap["launch_time"];
	screenData.fps_font_size = static_cast<int>(dataMap["fps_font_size"]);
	screenData.launch_particle_opacity = static_cast<int>(dataMap["launch_particle_opacity"]);
	screenData.fps_pos_x = dataMap["fps_pos_x"];
	screenData.fps_pos_y = dataMap["fps_pos_y"];
	screenData.game_next_level_spike = dataMap["game_next_level_spike"];

	playerData.size = dataMap["player_size"];
	playerData.start_position_x = dataMap["player_start_position_x"];
	playerData.start_position_y = dataMap["player_start_position_y"];
	playerData.start_position_angle = dataMap["player_start_position_angle"];
	playerData.speed = dataMap["player_speed"];
	playerData.turn_speed = dataMap["player_turn_speed"];
	playerData.bullet_speed = dataMap["player_bullet_speed"];
	playerData.bullet_shoot_delay = dataMap["player_bullet_shoot_delay"];
	playerData.bullet_lifetime = dataMap["player_bullet_lifetime"];
	playerData.bullet_size = dataMap["player_bullet_size"];
	playerData.sprite_cycle_time = dataMap["player_sprite_cycle_time"];
	playerData.dash_duration = dataMap["player_dash_duration"];
	playerData.dash_length = static_cast<int>(dataMap["player_dash_length"]);
	playerData.dash_time_delay = dataMap["player_dash_time_delay"];

	enemiesData.asteroid_spin = dataMap["enemy_asteroid_spin"];
	enemiesData.asteroid_speed = dataMap["enemy_asteroid_speed"];
	enemiesData.asteroid_size = dataMap["enemy_asteroid_size"];

	drawsData.outline_fill_background_opacity = static_cast<int>(dataMap["outline_fill_background_opacity"]);
	drawsData.outline_thickness = dataMap["outline_thickness"];

	timingsData.default_freeze_time = dataMap["default_freeze_time"];
	timingsData.default_enemy_spawn_time = dataMap["default_enemy_spawn_time"];

	return;
}