#pragma once
#ifndef FILEMENAGER_H
#define FILEMENAGER_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include <map>

using namespace std;

struct ScreenData {
	float padding;
    int framerate;
    float launch_time;
    int fps_font_size;
    int launch_particle_opacity;
    float fps_pos_x;
    float fps_pos_y;
    float game_next_level_spike;
};

struct PlayerData {
    float size;
    float start_position_x;
    float start_position_y;
    float start_position_angle;
    float speed;
    float turn_speed;
    float bullet_speed;
    float bullet_shoot_delay;
    float bullet_lifetime;
    float bullet_size;
    float sprite_cycle_time;
    float dash_time_delay;
    float dash_duration;
    int dash_length;
};

struct EnemiesData {
    float asteroid_spin;
    float asteroid_speed;
    float asteroid_size;
};

struct DrawsData {
	float outline_thickness;
	int outline_fill_background_opacity;
};

struct TimingsData {
	float default_freeze_time;
	float default_enemy_spawn_time;
};

class FileMenager {
private:
    char* fileName;

    static bool sortByFloatValue(const std::pair<std::string, float>& a, const std::pair<std::string, float>& b);
public:
    static PlayerData playerData;
    static ScreenData screenData;
    static EnemiesData enemiesData;
	static DrawsData drawsData;
	static TimingsData timingsData;
    static vector<pair<string, float>> highScore;
    FileMenager();
    ~FileMenager();

    void setFileName(const char* fileName);
 
    const char* getFileName() const;
    static vector<pair<string, float>> sortMapByFloat(const map<string, float>& inputMap);
    static void saveData(const string& fileName, const pair<string, int>& data);
    static map<string, float> getDataFromFile(const string& filename);
	void setDataFromFile() const;
};

#endif