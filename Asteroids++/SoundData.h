#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <thread>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace sf;
using namespace std;

enum class Sounds {
    LASER_SHOOT,
    EXPLOSION,
    DASH_ABILITY,
    DASH_ABILITY_RESTORE,
    PICKUP_1,
    PICKUP_2,
    PICKUP_3,
    PICKUP_4
};

class SoundData {
public:
    void loadAllSounds();
    static void play(Sounds);

    static unordered_map <Sounds, Sound> sounds;

private:
    unordered_map<Sounds, SoundBuffer> soundBuffers;
};

#endif