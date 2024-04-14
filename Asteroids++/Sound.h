#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <thread>
#include <iostream>

enum class Sounds {
    LASER_SHOOT,
    EXPLOSION
};

class Sound {
public:
    static void play(Sounds);
    void initSounds();
    void loadFile(Sounds);


    static std::unordered_map <std::string, sf::Sound> sounds;

private:
    const std::string soundDefaultDir = "./assets/sounds/";
    const std::string extension = ".wav";

    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

    std::string name;
    std::string filename;

};

#endif