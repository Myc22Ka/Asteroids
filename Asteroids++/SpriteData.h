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

using namespace sf;
using namespace std;
namespace fs = filesystem;
using namespace rapidjson;

enum class Sprites {
    SHIP,
    ASTEROID,
    MULTI_ASTEROID,
    SINGLE_ASTEROID,
    BULLET,
    EXPLOSION_1,
    EXPLOSION_2,
    EXPLOSION_3,
    EXPLOSION_4,
    DASHBAR,
    PICKUP_1,
    PICKUP_2,
    PICKUP_3,
    PICKUP_4,
    COLLECTED,
    CHEST
};

struct SpriteInfo
{
    Sprite sprite;
    Texture texture;
    vector<IntRect> frames;
    Sprites spriteType = Sprites();

    double currentSpriteLifeTime = 0;
    double defaultSpriteLifeTime = 0;
    size_t spriteState = 0;
    int rotation = 0;
    int spriteSize = 0;
    int hitboxSize = 0;
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

    void setRotation(Sprite& sprite, const int& angle);
    void updateSprite(Sprite& sprite, const vector<IntRect>& frames, const int& spriteState);
    void scaleSprite(Sprite& sprite, const int& spriteSize, const int& size);

    static unordered_map<Sprites, SpriteInfo> sprites;
};

#endif