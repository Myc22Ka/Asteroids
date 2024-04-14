#include "HealthBar.h"

HealthBar::HealthBar(float width, float height, sf::Color fillColor, sf::Color outlineColor, float maxValue)
    : maxWidth(width), currentValue(maxValue), maxValue(maxValue) {
    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(fillColor);
    outline.setSize(sf::Vector2f(width, height));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2);

    outline.setOutlineColor(outlineColor);
}

void HealthBar::updateBar(const sf::Vector2f& position) {
    float barWidth = (currentValue / maxValue) * maxWidth;
    bar.setSize(sf::Vector2f(barWidth, bar.getSize().y));
    bar.setPosition(position);
    outline.setPosition(position);
}

void HealthBar::setCurrentValue(float value) {
    currentValue = value;
}

void HealthBar::draw(sf::RenderWindow& window) {
    window.draw(outline);
    window.draw(bar);
}
