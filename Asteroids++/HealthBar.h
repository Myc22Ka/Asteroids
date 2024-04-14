#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar {
private:
    sf::RectangleShape bar;
    sf::RectangleShape outline;
    float maxWidth;
    float currentValue;
    float maxValue;

public:
    HealthBar(float width, float height, sf::Color fillColor, sf::Color outlineColor, float maxValue);
    void updateBar(const sf::Vector2f& position);
    void setCurrentValue(float value);
    void draw(sf::RenderWindow& window);
};

#endif