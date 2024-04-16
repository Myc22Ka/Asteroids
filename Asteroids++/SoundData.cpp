#include "SoundData.h"
#include "FileMenager.h"

std::unordered_map <std::string, sf::Sound> SoundData::sounds;

const std::string LASER_SHOOT = "laserShoot";
const std::string EXPLOSION = "explosion";

void SoundData::loadFile(Sounds str)
{
    filename = soundDefaultDir;

    switch (str) {
    case Sounds::LASER_SHOOT:
        name = LASER_SHOOT;
        break;
    case Sounds::EXPLOSION:
        name = EXPLOSION;
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

    sounds[name].setBuffer(soundBuffers[name]);
}

void SoundData::initSounds()
{
    loadFile(Sounds::LASER_SHOOT);
    loadFile(Sounds::EXPLOSION);

}

void SoundData::play(Sounds name)
{
    switch (name) {
    case Sounds::LASER_SHOOT:
        sounds[LASER_SHOOT].play();
        break;
    case Sounds::EXPLOSION:
        sounds[EXPLOSION].play();
        break;
    default:
        std::cerr << "Error: Cannot play Sound\n";
        return;
    }
}
