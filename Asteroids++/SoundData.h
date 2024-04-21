#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <thread>
#include <iostream>

using namespace sf;
using namespace std;

enum class Sounds {
    LASER_SHOOT,
    EXPLOSION,
    DASH_ABILITY,
    DASH_ABILITY_RESTORE,
    PICKUP
};

class SoundData {
public:
    static void play(Sounds);
    void initSounds();
    void loadFile(Sounds);


    static unordered_map <string, Sound> sounds;

private:
    unordered_map<string, SoundBuffer> soundBuffers;

    string name;
    string filename;

};

#endif