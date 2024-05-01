#include "SoundData.h"
#include "FileMenager.h"

unordered_map <Sounds, Sound> SoundData::sounds;

const string defaultDir = "./assets/sounds/";

const vector<pair<string, Sounds>> objects = {
    {"laserShoot" , Sounds::LASER_SHOOT},
    {"explosion" , Sounds::EXPLOSION},
    {"dashAbility", Sounds::DASH_ABILITY},
    {"regainDash", Sounds::DASH_ABILITY_RESTORE},
    {"extrabullet", Sounds::PICKUP_EXTRA_BULLET},
    {"extraspeed", Sounds::PICKUP_EXTRA_SPEED},
    {"extratime", Sounds::PICKUP_EXTRA_TIME},
    {"shield", Sounds::PICKUP_SHIELD},
    {"drunkmode", Sounds::PICKUP_DRUNKMODE},
    {"heart1UP", Sounds::HEART1UP},
    {"freeze", Sounds::FREEZE},
    {"wind", Sounds::WIND}
};

void SoundData::loadAllSounds()
{
    Sounds type = {};

    for (const auto& entry : fs::directory_iterator(defaultDir)) {
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".wav") {
            const auto filename = entry.path().stem().string();

            for (const auto& obj : objects) {
                if (obj.first == filename) {
                    type = obj.second;
                    break;
                }
            }

            if (!soundBuffers[type].loadFromFile(entry.path().string())) {
                cout << "Error: Could not find sound file: " << entry.path().string() << endl;
                return;
            }

            sounds[type].setBuffer(soundBuffers[type]);
        }
    }
}

void SoundData::play(Sounds name)
{
    sounds[name].play();
}

void SoundData::stop(Sounds name){
    thread t([name]() {
        while (sounds[name].getStatus() == sf::Sound::Playing && sounds[name].getVolume() > 5) {
            sounds[name].setVolume(floor(sounds[name].getVolume() - 1));

            sf::sleep(sf::milliseconds(10));
        }
        sounds[name].setVolume(100);

        sounds[name].stop();

    });

    t.detach();
}
