#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar {
private:
    sf::RectangleShape bar;
    sf::RectangleShape outline;
    double maxWidth;
    double currentValue;
    double maxValue;

public:
    HealthBar(double width, double height, sf::Color fillColor, sf::Color outlineColor, double maxValue);
    void updateBarValue();
    void updateBar(const sf::Vector2f& position);
    void setCurrentValue(double value);
    void draw(sf::RenderWindow& window) const;
};

#endif