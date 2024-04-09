#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <iostream>

enum class Names {
    LASER_SHOOT,
    EXPLOSION
};

class Sound {
public:
    Sound();
    ~Sound();
    void setFileName(Names filename);
    void loadAndPlay();
    void stopSoundThread();

private:
    std::string filename;
    std::thread soundThread;
    std::atomic<bool> threadRunning;
};