#pragma once
#ifndef FILEMENAGER_H
#define FILEMENAGER_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>

struct ScreenData {
    float size_height;
    float size_width;
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
    float sprite_cycle_time;
};

struct EnemiesData {
    float asteroid_spin;
    float asteroid_speed;
    float asteroid_spawn_time;
};

class FileMenager {
private:
    char* fileName;
public:
    static PlayerData playerData;
    static ScreenData screenData;
    static EnemiesData enemiesData;
    FileMenager();
    ~FileMenager();

    void setFileName(const char*);

    const char* getFileName() const;
    void setDataFromFile();
};

#endif