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
    int size_height;
    int size_width;
};

struct PlayerData {
    int size;
    int start_position_x;
    int start_position_y;
    int start_position_angle;
    int speed;
    int turn_speed;
    int bullet_speed;
};

class FileMenager {
private:
    char* fileName;
public:
    static PlayerData playerData;
    static ScreenData screenData;
    FileMenager();
    ~FileMenager();

    void setFileName(const char*);

    const char* getFileName() const;
    void setDataFromFile();
};

#endif