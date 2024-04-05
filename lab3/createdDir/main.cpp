#include <iostream>
#include "FileMenager.h"

import WindowBox;

int main()
{
    FileMenager fileMenager;
    fileMenager.setFileName("config.txt");
    fileMenager.setDataFromFile();

    WindowBox window;

    window.displayWindow();
}