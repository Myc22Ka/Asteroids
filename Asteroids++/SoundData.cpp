#include "SoundData.h"
#include "FileMenager.h"

unordered_map <Sounds, Sound> SoundData::sounds;

const string defaultDir = "./assets/sounds/";

const vector<pair<string, Sounds>> objects = {
    {"laserShoot" , Sounds::LASER_SHOOT},
    {"explosion" , Sounds::EXPLOSION},
    {"dashAbility", Sounds::DASH_ABILITY},
    {"regainDash", Sounds::DASH_ABILITY_RESTORE},
    {"pickup1", Sounds::PICKUP_1},
    {"pickup2", Sounds::PICKUP_2},
    {"pickup3", Sounds::PICKUP_3},
    {"pickup4", Sounds::PICKUP_4},
    {"heart1UP", Sounds::HEART1UP}
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
