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

    float player_bullet_poison_damage;
    int player_bullet_poison_amount;
};

struct EnemiesData {
    float asteroid_spin;
    float asteroid_speed;
    float asteroid_size;

    float enemy_blackhole_increse_size;

    float enemy_tower_spawn_chance;
    float enemy_strauner_spawn_chance;
    float enemy_invader_spawn_chance;
    float enemy_blackhole_spawn_chance;
    float enemy_comet_spawn_chance;
    float enemy_multiasteroid_spawn_chance;
    float enemy_singleasteroid_spawn_chance;
};

struct DrawsData {
	float outline_thickness;
	int outline_fill_background_opacity;
};

struct TimingsData {
	float default_freeze_time;
	float default_enemy_spawn_time;
    float default_fps_delay;
    float default_bullet_homing_time;
    float default_crit_timer;
    int default_poison_dose_time;
    float default_hit_effect_time;
};

struct GameData {
    int max_level;
    int starting_level;
    int debug_mode;
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
    static GameData gameData;
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