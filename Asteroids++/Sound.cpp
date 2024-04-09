#include "Sound.h"
#include "FileMenager.h"

Sound::Sound() : threadRunning(false) {}

Sound::~Sound() {
    stopSoundThread();
}

void Sound::setFileName(Names str)
{
    const std::string soundDefaultDir = "./assets/sounds/";
    const std::string extension = ".wav";

    filename = soundDefaultDir;

    switch (str) {
    case Names::LASER_SHOOT:
        name = "laserShoot";
        break;
    case Names::EXPLOSION:
        name = "explosion";
        break;
    default:
        std::cerr << "Error: Invalid Sound Name\n";
        return;
    }

    filename += name + extension;

    if (!soundBuffers[name].loadFromFile(filename)) {
        std::cout << "Error: Could not find sound file: " << filename << std::endl;
        return;
    }
}

void Sound::loadAndPlay() {
    auto& buffer = soundBuffers[name];
    // Create a new thread to play the sound
    std::thread soundThread([this, buffer]() {
        sf::Sound sound;
        // Create a sound instance and set its buffer
        sound.setBuffer(buffer);

        // Play the sound
        sound.play();

        // Wait until the sound finishes playing
        while (sound.getStatus() == sf::Sound::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sound.getBuffer()->getDuration().asMilliseconds()));
        }
    });

    // Detach the thread so it can run independently
    soundThread.detach();
}

void Sound::stopSoundThread() {
    if (threadRunning) {
        threadRunning = false;
        if (soundThread.joinable()) {
            soundThread.join();
        }
    }
}