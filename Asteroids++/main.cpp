#include <iostream>
#include "FileMenager.h"
#include "SoundData.h"
#include "SpriteData.h"

import WindowBox;

int main()
{
    FileMenager fileMenager;
    fileMenager.setFileName("config.txt");
    fileMenager.setDataFromFile();

    SoundData sounds;
    sounds.initSounds();

    SpriteData sprite;
    sprite.loadAllSprites();

    WindowBox window;

    window.displayWindow();
}