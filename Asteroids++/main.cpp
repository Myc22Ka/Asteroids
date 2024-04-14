#include <iostream>
#include "FileMenager.h"
#include "Sound.h"

import WindowBox;

int main()
{
    FileMenager fileMenager;
    fileMenager.setFileName("config.txt");
    fileMenager.setDataFromFile();

    Sound sounds;
    sounds.initSounds();

    WindowBox window;

    window.displayWindow();
}