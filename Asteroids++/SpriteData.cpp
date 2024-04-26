#include "SpriteData.h"

const auto defaultDir = "./assets/sprites";

const vector<pair<string, Sprites>> objects = {
        {"ship", Sprites::SHIP},
        {"multiAsteroid", Sprites::MULTI_ASTEROID},
        {"singleAsteroid", Sprites::SINGLE_ASTEROID},
        {"singleBullet", Sprites::SINGLE_BULLET},
        {"piercingBullet", Sprites::PIERCING_BULLET},
        {"explosion1", Sprites::EXPLOSION_1},
        {"explosion2", Sprites::EXPLOSION_2},
        {"explosion3", Sprites::EXPLOSION_3},
        {"explosion4", Sprites::EXPLOSION_4},
        {"dashBar", Sprites::DASHBAR},
        {"pickup1", Sprites::PICKUP_1},
        {"pickup2", Sprites::PICKUP_2},
        {"pickup3", Sprites::PICKUP_3},
        {"pickup4", Sprites::PICKUP_4},
        {"heart1UP", Sprites::HEART1UP},
        {"pickupPiercing", Sprites::PICKUP_PIERCING},
        {"collected", Sprites::COLLECTED},
        {"heart", Sprites::HEART},
        {"shield", Sprites::SHIELD}
};

unordered_map<Sprites, SpriteInfo> SpriteData::sprites;

void SpriteData::populateSpriteInfo(const string& objectKey, const Sprites& spriteType)
{
    if (document.HasMember(objectKey.c_str()) && document[objectKey.c_str()].IsObject()) {
        const Value& object = document[objectKey.c_str()];
        sprites[spriteType].spriteType = spriteType;
    
        if (object.HasMember("hitboxSize") && object["hitboxSize"].IsNumber()) {
            sprites[spriteType].hitboxSize = object["hitboxSize"].GetInt();
        }
        if (object.HasMember("spriteSize") && object["spriteSize"].IsNumber()) {
            sprites[spriteType].spriteSize = object["spriteSize"].GetInt();
        }
        if (object.HasMember("rotation") && object["rotation"].IsNumber()) {
            sprites[spriteType].rotation = object["rotation"].GetInt();
        }
        if (object.HasMember("spriteState") && object["spriteState"].IsNumber()) {
            sprites[spriteType].spriteState = object["spriteState"].GetInt();
        }
        if (object.HasMember("defaultSpriteLifeTime") && object["defaultSpriteLifeTime"].IsNumber()) {
            sprites[spriteType].defaultSpriteLifeTime = object["defaultSpriteLifeTime"].GetDouble();
        }
        if (object.HasMember("currentSpriteLifeTime") && object["currentSpriteLifeTime"].IsNumber()) {
            sprites[spriteType].currentSpriteLifeTime = object["currentSpriteLifeTime"].GetDouble();
        }
    }
}

void SpriteData::loadJSONData(const string& filename) {
    string jsonString;
    ifstream jsonFile(filename);
    if (!jsonFile.is_open()) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(jsonFile, line)) {
        jsonString += line + "\n";
    }
    jsonFile.close();

    document.Parse(jsonString.c_str());

    if (document.IsObject()) {
        for (auto& obj : objects) {
            populateSpriteInfo(obj.first, obj.second);
        }
    }
    else {
        cerr << "Failed to parse JSON from file " << filename << endl;
        return;
    }
}

template<typename T>
inline const T SpriteData::getJSONProperty(const string& property, Value& spriteData)
{
    if (spriteData.HasMember(property.c_str()) && spriteData[property.c_str()].IsNumber()) {
        return static_cast<T>(spriteData[property.c_str()].GetDouble());
    }
    return T();
}


void SpriteData::loadAllSprites()
{
    Sprites type = {};

    for (const auto& entry : fs::directory_iterator(defaultDir))
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".json") loadJSONData(entry.path().string());

    for (const auto& entry : fs::directory_iterator(defaultDir)) {
        if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".png") {
            const auto filename = entry.path().stem().string();


            for (const auto& obj : objects) {
                if (obj.first == filename) {
                    type = obj.second;
                    break;
                }
            }

            if (!sprites[type].texture.loadFromFile(entry.path().string())) {
                cout << "Error: Invalid Sprite Name\n" << endl;
                return;
            }

            sprites[type].texture.setSmooth(true);

            const auto w = getTextureWidth(sprites[type].texture) / sprites[type].spriteSize;
            const auto h = getTextureHeight(sprites[type].texture) / sprites[type].spriteSize;
            const auto n = w * h;

            int y = 0;
            for (int i = 0; i < h; i++)
            {
                int x = 0;
                for (int i = 0; i < w; i++)
                {
                    const auto rect = IntRect(x, y, sprites[type].spriteSize, sprites[type].spriteSize);
                    sprites[type].frames.push_back(rect);
                    x += sprites[type].spriteSize;
                }
                y += sprites[type].spriteSize;
            }

            sprites[type].sprite.setTexture(sprites[type].texture);
            sprites[type].sprite.setTextureRect(sprites[type].frames[0]);
            sprites[type].sprite.rotate(sprites[type].rotation);

            const Rect center = sprites[type].sprite.getLocalBounds();
            sprites[type].sprite.setOrigin((int)center.width >> 1, (int)center.height >> 1);
        }
    }
}

SpriteInfo SpriteData::getSprite(const Sprites& spriteType)
{
    return sprites[spriteType];
}

void SpriteData::setRotation(Sprite& sprite, const int& angle)
{
    sprite.rotate(angle);
}

void SpriteData::updateSprite(Sprite& sprite, const vector<IntRect>& frames, const int& spriteState)
{
    sprite.setTextureRect(frames[spriteState]);
}

void SpriteData::scaleSprite(Sprite& sprite, const int& spriteSize, const int& size)
{
    const double scale = (double)size / spriteSize;
    sprite.setScale(scale, scale);
}

const int SpriteData::getTextureWidth(const Texture& texture)
{
    return texture.getSize().x;
}

const int SpriteData::getTextureHeight(const Texture& texture)
{
    return texture.getSize().y;
}