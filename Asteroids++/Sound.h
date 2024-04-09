#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <thread>
#include <iostream>

enum class Names {
    LASER_SHOOT,
    EXPLOSION
};

class Sound {
public:

    Sound();
    ~Sound();

    void setFileName(Names str);
    void loadAndPlay();
    void stopSoundThread();

private:
    static const std::string soundDefaultDir;
    static const std::string extension;

    std::string name;
    std::string filename;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::thread soundThread;
    bool threadRunning;
};

#endif