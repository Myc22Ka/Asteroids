#pragma once
#ifndef DASHBAR_H
#define DASHBAR_H

#include <SFML/Graphics.hpp>
#include "SpriteData.h"

using namespace sf;
using namespace std;

class DashBar : public SpriteData {
private:
    Vector2f position;
    double currentValue = 1;
    SpriteInfo spriteInfo;
public:
    DashBar();

    void update(double deltaTime);
    void draw(RenderWindow& window) const;
};

#endif