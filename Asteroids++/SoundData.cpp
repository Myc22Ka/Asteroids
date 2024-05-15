#include "SoundData.h"
#include "FileMenager.h"

unordered_map <Sounds, Sound> SoundData::sounds;

const string defaultDir = "./assets/sounds/";

const vector<pair<string, Sounds>> objects = {
    {"laserShoot1" , Sounds::LASER_SHOOT1},
    {"laserShoot2" , Sounds::LASER_SHOOT2},
    {"laserShoot3" , Sounds::LASER_SHOOT3},
    {"laserShoot4" , Sounds::LASER_SHOOT4},
    {"alienshoot1", Sounds::ALIEN_SHOOT1},
    {"doubleshot", Sounds::PICKUP_DOUBLESHOOT},
    {"tripleshot", Sounds::PICKUP_TRIPLESHOOT},
    {"quadshot", Sounds::PICKUP_QUADSHOOT},
    {"explosion" , Sounds::EXPLOSION},
    {"destroy", Sounds::DESTROY},
    {"dashAbility", Sounds::DASH_ABILITY},
    {"extrabullet", Sounds::PICKUP_EXTRA_BULLET},
    {"extraspeed", Sounds::PICKUP_EXTRA_SPEED},
    {"extratime", Sounds::PICKUP_EXTRA_TIME},
    {"times2", Sounds::PICKUP_TIMES_2},
    {"times5", Sounds::PICKUP_TIMES_5},
    {"shield", Sounds::PICKUP_SHIELD},
    {"drunkmode", Sounds::PICKUP_DRUNKMODE},
    {"heart1UP", Sounds::HEART1UP},
    {"freeze", Sounds::FREEZE},
    {"wind", Sounds::WIND},
	{"goodbye", Sounds::GOODBYE},
    {"shieldActive", Sounds::ACTIVE_SHIELD},
	{"ping", Sounds::PING},
	{"hit", Sounds::HIT},
    {"critHit", Sounds::CRITHIT},
    {"ambient", Sounds::AMBIENT}
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

void SoundData::playLooped(Sounds name) {
    sounds[name].setLoop(true);
    sounds[name].play();
}

void SoundData::renev(Sounds name) {
    thread t([name]() {
        while (sounds[name].getStatus() == Sound::Playing && sounds[name].getVolume() < 95) {
            sounds[name].setVolume(floor(sounds[name].getVolume() + 1));

            sleep(milliseconds(30));
        }
        sounds[name].setVolume(100);
        sounds[name].play();

    });

    t.detach();
}

void SoundData::stop(Sounds name){
    thread t([name]() {
        while (sounds[name].getStatus() == Sound::Playing && sounds[name].getVolume() > 5) {
            sounds[name].setVolume(floor(sounds[name].getVolume() - 1));

            sleep(milliseconds(30));
        }
        sounds[name].setVolume(0);
        sounds[name].pause();

    });

    t.detach();
}
