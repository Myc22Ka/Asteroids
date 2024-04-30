#include "HealthBar.h"

HealthBar::HealthBar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position)
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
    float barWidth = (currentValue / maxValue) * maxWidth;

    bar.setSize(Vector2f(barWidth, bar.getSize().y));
}

void HealthBar::updateBar(const Vector2f& position) {
    float barWidth = (currentValue / maxValue) * maxWidth;
    bar.setSize(Vector2f(barWidth, bar.getSize().y));
    bar.setPosition(position);
    outline.setPosition(position);
}

void HealthBar::setCurrentValue(const float& value) {
    currentValue = value;
}

void HealthBar::draw(RenderWindow& window) const {
    window.draw(outline);
    window.draw(bar);
}
