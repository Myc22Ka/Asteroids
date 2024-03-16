module;

#include <iostream>
#include <vector>
#include <algorithm>
#include "BasicArray.h"

module BasicArray;

void display(const std::vector<int>& array) {
	for (auto& i : array)
		std::cout << i << " ";
	std::cout << std::endl;
}

void sortVector(std::vector<int>& array){
	std::sort(array.begin(), array.end());
}

// to BasicArray.h file

BasicArray::BasicArray(const std::vector<int>& v) : array(v) {}

void BasicArray::displayArray() const
{
	for (auto& i : array)
		std::cout << i << " ";
	std::cout << std::endl;
}

void BasicArray::sortArray()
{
	std::sort(array.begin(), array.end());
}
