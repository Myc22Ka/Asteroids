#include <iostream>
#include "FileMenager.h"
#include "SoundData.h"
#include "SpriteData.h"
#include "WindowBox.h"

using namespace sf;
using namespace std;

int main()
{
    FileMenager fileMenager;
    fileMenager.setFileName("config.txt");
    fileMenager.setDataFromFile();

    SoundData sounds;
    sounds.loadAllSounds();

    SpriteData sprite;
    sprite.loadAllSprites();

    WindowBox window;

    window.displayWindow();
}