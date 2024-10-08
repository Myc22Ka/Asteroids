#pragma once
#ifndef PLAYERHEALTHUI_H
#define PLAYERHEALTHUI_H

#include <SFML/Graphics.hpp>
#include "SpriteData.h"

using namespace sf;
using namespace std;

class PlayerHealthUI : public SpriteData {
private:
    Vector2f position;
    SpriteInfo spriteInfo;

    bool removeHealthFromPlayer;
public:
    PlayerHealthUI(const float& offset);

    void update(float deltaTime);
    void draw(RenderWindow& window) const;
    void setSpriteState(const int& newState);

    void removeHealth();

    float offset;
};

#endif