#include "HealthBar.h"

HealthBar::HealthBar(double width, double height, sf::Color fillColor, sf::Color outlineColor, double maxValue)
    : maxWidth(width), currentValue(maxValue), maxValue(maxValue) {
    bar.setSize(sf::Vector2f(width, height));
    bar.setFillColor(fillColor);
    outline.setSize(sf::Vector2f(width, height));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineThickness(2);

    outline.setOutlineColor(outlineColor);
}

void HealthBar::updateBarValue() {
    double barWidth = (currentValue / maxValue) * maxWidth;

    bar.setSize(sf::Vector2f(barWidth, bar.getSize().y));
}

void HealthBar::updateBar(const sf::Vector2f& position) {
    double barWidth = (currentValue / maxValue) * maxWidth;
    bar.setSize(sf::Vector2f(barWidth, bar.getSize().y));
    bar.setPosition(position);
    outline.setPosition(position);
}

void HealthBar::setCurrentValue(double value) {
    currentValue = value;
}

void HealthBar::draw(sf::RenderWindow& window) const {
    window.draw(outline);
    window.draw(bar);
}
