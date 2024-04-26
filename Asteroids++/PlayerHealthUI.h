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
public:
    PlayerHealthUI(const double& offset);

    void update(float deltaTime);
    void draw(RenderWindow& window) const;
    void setSpriteState(const int& newState);

    bool death = false;
    double offset;
};

#endif