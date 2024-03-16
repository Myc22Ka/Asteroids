#pragma once
#ifndef BASIC_ARRAY_H
#define BASIC_ARRAY_H

#include <vector>

class BasicArray {
    std::vector<int> array;

public:
    BasicArray(const std::vector<int>&);

    void displayArray() const;
    void sortArray();
};

#endif // BASIC_ARRAY_H