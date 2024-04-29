#include "HealthBar.h"

HealthBar::HealthBar(double width, double height, Color fillColor, Color outlineColor, double maxValue, Vector2f position)
    : maxWidth(width), currentValue(maxValue), maxValue(maxValue) {
    bar.setSize(Vector2f(width, height));
    bar.setFillColor(fillColor);
    outline.setSize(Vector2f(width, height));
    outline.setFillColor(Color::Transparent);
    outline.setOutlineThickness(2);

    outline.setOutlineColor(outlineColor);

    updateBar(position);
}

void HealthBar::updateBarValue() {
    double barWidth = (currentValue / maxValue) * maxWidth;

    bar.setSize(Vector2f(barWidth, bar.getSize().y));
}

void HealthBar::updateBar(const Vector2f& position) {
    double barWidth = (currentValue / maxValue) * maxWidth;
    bar.setSize(Vector2f(barWidth, bar.getSize().y));
    bar.setPosition(position);
    outline.setPosition(position);
}

void HealthBar::setCurrentValue(double value) {
    currentValue = value;
}

void HealthBar::draw(RenderWindow& window) const {
    window.draw(outline);
    window.draw(bar);
}
