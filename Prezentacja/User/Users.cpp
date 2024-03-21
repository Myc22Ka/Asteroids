#include "Users.h"
#include <fstream>
#include <vector>
#include <iostream>

void Users::display(const std::smatch& matches)
{
    for (auto& i : matches)
        std::cout << i << " ";
    std::cout << std::endl;
}

std::vector<std::string> Users::getDataFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::vector<std::string> data;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filePath << std::endl;
        return data;
    }

    while (std::getline(file, line)) {
        data.push_back(line);
    }

    file.close();
    return data;
}

void Users::getPhoneNumber()
{
    auto response = getDataFromFile("users.txt");

    // your code here
}

void Users::countMales()
{
    auto response = getDataFromFile("users.txt");
    int boysAmount = 0;

    // your code here

    std::cout << "TEAM BOYS: " << boysAmount << " | " << "TEAM GIRLS: " << response.size() - boysAmount << std::endl;
}

void Users::getFemaleURL(){
    auto response = getDataFromFile("users.txt");

    // your code here
}
