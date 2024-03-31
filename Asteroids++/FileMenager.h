#pragma once
#ifndef FILEMENAGER_H
#define FILEMENAGER_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <sstream>

class FileMenager {
private:
    static FileMenager* instance;
    char* fileName;
    std::vector<std::pair<std::string, double>> dataFromFile{};

    FileMenager();
    FileMenager(const FileMenager&) = delete;
    FileMenager& operator=(const FileMenager&) = delete;

public:
    ~FileMenager();
    static FileMenager* getInstance();

    void setFileName(const char*);

    const char* getFileName() const;
    void setDataFromFile();

    const std::vector<std::pair<std::string, double>>& getDataFromFile() const;
};

const double& getValueFromProperty(const std::string&);

#endif