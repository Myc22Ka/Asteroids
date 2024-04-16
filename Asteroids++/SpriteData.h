#pragma once
#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include <SFML/Graphics.hpp>
#include "FileMenager.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <thread>
#include <iostream>
#include <condition_variable>

using namespace sf;
using namespace std;
namespace fs = std::filesystem;

enum class Sprites {
    SHIP,
    ASTEROID,
    BULLET,
    EXPLOSION
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
    int size = 0;
    bool isAnimating = false;
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
    void loadFullCycleSprite(SpriteInfo& spriteInfo, float deltaTime);

    static unordered_map<string, SpriteInfo> sprites;
};

#endif