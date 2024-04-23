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
    PlayerHealthUI(Vector2f position);

    void update();
    void draw(RenderWindow& window) const;
};

#endif