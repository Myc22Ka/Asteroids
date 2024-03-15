module;

#include <iostream>;
#include <vector>;

module Tablica.xd;

void displayTab(std::vector<int> tablica)
{
	for (auto& i : tablica)
		std::cout << i << " ";
	std::cout << std::endl;
}