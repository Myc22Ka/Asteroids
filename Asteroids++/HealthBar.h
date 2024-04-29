#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

using namespace sf;

class HealthBar {
private:
    RectangleShape bar;
    RectangleShape outline;
    double maxWidth;
    double currentValue;
    double maxValue;

public:
    HealthBar(double width, double height, Color fillColor, Color outlineColor, double maxValue, Vector2f position);
    void updateBarValue();
    void updateBar(const Vector2f& position);
    void setCurrentValue(double value);
    void draw(RenderWindow& window) const;
};

#endif