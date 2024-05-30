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
    LASER_SHOOT1,
    LASER_SHOOT2,
    LASER_SHOOT3,
    LASER_SHOOT4,
    ALIEN_SHOOT1,
    DESTROY,
    EXPLOSION,
    DASH_ABILITY,
    DASH_ABILITY_RESTORE,
    PICKUP_EXTRA_BULLET,
    PICKUP_EXTRA_SPEED,
    PICKUP_EXTRA_TIME,
    PICKUP_SHIELD,
    PICKUP_DRUNKMODE,
    PICKUP_TIMES_2,
    PICKUP_TIMES_5,
    PICKUP_DOUBLESHOOT,
    PICKUP_TRIPLESHOOT,
    PICKUP_QUADSHOOT,
    FREEZE,
    HEART1UP,
    WIND,
    GOODBYE,
    PING,
    HIT,
    CRITHIT,
    ACTIVE_SHIELD,
    AMBIENT
};

class SoundData {
public:
    void loadAllSounds();
    static void play(Sounds name);
    static void playLooped(Sounds name);
    static void renev(Sounds name);
    static void pause(Sounds name);
    static void stop(Sounds name);

    static void modifySound(Sounds name);
    static void unmodifySound(Sounds name);
    static void recoverSound(Sounds name);

    static bool isSoundPlaying(Sounds name);

    static unordered_map <Sounds, Sound> sounds;

private:
    unordered_map<Sounds, SoundBuffer> soundBuffers;
};

#endif