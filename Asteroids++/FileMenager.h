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
	char* fileName;
	std::vector<std::pair<std::string, double>> dataFromFile {};

public: 
	FileMenager();
	~FileMenager();

	void setFileName(const char*);
	const char* getFileName() const;

	void setDataFromFile();
	const std::vector<std::pair<std::string, double>>& getDataFromFile() const;

	const double& getPropertyValue(const std::string&) const;
};

#endif