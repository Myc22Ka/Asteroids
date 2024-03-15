module;

#include <iostream>
#include <vector>
#include <algorithm>

module BasicArray;

void display(const std::vector<int>& array) {
	for (auto& i : array)
		std::cout << i << " ";
	std::cout << std::endl;
}

void sortVector(std::vector<int>& array){
	std::sort(array.begin(), array.end());
}
