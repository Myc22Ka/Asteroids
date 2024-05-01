#pragma once
#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include <SFML/Graphics.hpp>
#include "FileMenager.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <iostream>
#include "rapidjson/document.h"
#include <regex>

using namespace sf;
using namespace std;
namespace fs = filesystem;
using namespace rapidjson;

enum class Sprites {
    SHIP,
    ASTEROID,
    MULTI_ASTEROID,
    SINGLE_ASTEROID,
    SINGLE_BULLET,
    PIERCING_BULLET,
    HOMING_BULLET,
    EXPLOSION_1,
    EXPLOSION_2,
    EXPLOSION_3,
    EXPLOSION_4,
    DASHBAR,
    PICKUP_EXTRA_BULLET,
    PICKUP_EXTRA_SPEED,
    PICKUP_EXTRA_TIME,
    PICKUP_SHIELD,
    PICKUP_DRUNKMODE,
    PICKUP_FREEZE,
    PICKUP_TIMES_2,
    PICKUP_TIMES_5,
    HEART1UP,
    PICKUP_PIERCING,
    COLLECTED,
    HEART,
    SHIELD,
    WIND
};

struct SpriteInfo
{
    Sprite sprite;
    Texture texture;
    vector<IntRect> frames;
    Sprites spriteType = Sprites();

    double currentSpriteLifeTime = 0;
    double defaultSpriteLifeTime = 0;
    int spriteState = 0;
    float rotation = 0;
    int spriteSize = 0;
    float hitboxSize = 0;
};

class SpriteData {
private:
    const int getTextureHeight(const Texture& texture);
    const int getTextureWidth(const Texture& texture);

    Document document;
    void populateSpriteInfo(const string& objectKey, const Sprites& spriteType);

public:
    void loadJSONData(const string& filename);
    template<typename T>
    const T getJSONProperty(const string& property, Value& spriteData);

    void loadAllSprites();

    SpriteInfo getSprite(const Sprites &spriteType);

    void setRotation(Sprite& sprite, const float& angle);
    void updateSprite(Sprite& sprite, const vector<IntRect>& frames, const int& spriteState);
    void scaleSprite(Sprite& sprite, const int& spriteSize, const float& size);

    static unordered_map<Sprites, SpriteInfo> sprites;
};

#endif