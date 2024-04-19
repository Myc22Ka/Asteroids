#pragma once
#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include <SFML/Graphics.hpp>
#include "FileMenager.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace sf;
using namespace std;
namespace fs = filesystem;

enum class Sprites {
    SHIP,
    ASTEROID,
    BULLET,
    EXPLOSION_1,
    EXPLOSION_2,
    EXPLOSION_3,
    EXPLOSION_4
};

struct SpriteInfo
{
    Sprite sprite;
    Texture texture;
    vector<IntRect> frames;
    Sprites spriteType = Sprites();

    float spriteLifeTime = 0.0f;
    int spriteState = 0;
    int rotation = 0;
    float size = 0;
};

class SpriteData {
private:
    void initSprite(const string& filename);
    const int getTextureHeight(const Texture& texture);
    const int getTextureWidth(const Texture& texture);
public:
    void loadAllSprites();

    SpriteInfo getSprite(const Sprites &spriteType);

    void setRotation(Sprite& sprite, const int& angle);
    void updateSprite(Sprite& sprite, const vector<IntRect>& frames, const int& spriteState);
    void scaleSprite(Sprite& sprite, const int& spriteSize, const int& size);

    static unordered_map<string, SpriteInfo> sprites;
};

#endif