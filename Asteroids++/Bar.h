#pragma once
#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SpriteData.h"

using namespace sf;
using namespace std;

class Bar : public SpriteData {
private:
    Color fillColor; 
    Color outlineColor;

    RectangleShape bar;
    RectangleShape outline;
    SpriteInfo spriteInfo;
    float maxWidth;
    float value;
    float maxValue;

    float width;
    float height;
    Vector2f position;

public:
    Bar();
    Bar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position);
    Bar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position, Sprites spriteType);

    const float getValue() const;
    const float getMaxWidth() const;
    void setMaxValue(const float& newMaxValue);

    void updateValue(const float& newValue);

    void render();
    void draw(RenderWindow& window) const;

    void updatePosition(const Vector2f& position);
};

#endif