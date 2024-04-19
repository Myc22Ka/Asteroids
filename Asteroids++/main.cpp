#include <iostream>
#include "FileMenager.h"
#include "SoundData.h"
#include "SpriteData.h"

using namespace sf;
using namespace std;

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