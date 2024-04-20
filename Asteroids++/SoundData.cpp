#include "SoundData.h"
#include "FileMenager.h"

unordered_map <string, Sound> SoundData::sounds;

const string soundDefaultDir = "./assets/sounds/";
const string extension = ".wav";

const string LASER_SHOOT = "laserShoot";
const string EXPLOSION = "explosion";
const string DASH_ABILITY = "dashAbility";
const string DASH_ABILITY_RESTORE = "regainDash";

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
    case Sounds::DASH_ABILITY:
        name = DASH_ABILITY;
        break;
    case Sounds::DASH_ABILITY_RESTORE:
        name = DASH_ABILITY_RESTORE;
        break;
    default:
        cerr << "Error: Invalid Sound Name\n";
        return;
    }

    filename += name + extension;

    if (!soundBuffers[name].loadFromFile(filename)) {
        cout << "Error: Could not find sound file: " << filename << endl;
        return;
    }

    sounds[name].setBuffer(soundBuffers[name]);
}

void SoundData::initSounds()
{
    loadFile(Sounds::LASER_SHOOT);
    loadFile(Sounds::EXPLOSION);
    loadFile(Sounds::DASH_ABILITY);
    loadFile(Sounds::DASH_ABILITY_RESTORE);
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
    case Sounds::DASH_ABILITY:
        sounds[DASH_ABILITY].play();
        break;
    case Sounds::DASH_ABILITY_RESTORE:
        sounds[DASH_ABILITY_RESTORE].play();
        break;
    default:
        cerr << "Error: Cannot play Sound\n";
        return;
    }
}
