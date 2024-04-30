#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

using namespace sf;

class HealthBar {
private:
    RectangleShape bar;
    RectangleShape outline;
    float maxWidth;
    float currentValue;
    float maxValue;

public:
    HealthBar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position);
    void updateBarValue();
    void updateBar(const Vector2f& position);
    void setCurrentValue(const float& value);
    void draw(RenderWindow& window) const;
};

#endif