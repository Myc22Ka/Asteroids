#include "Bar.h"

Bar::Bar(): maxWidth(0.0f), width(0.0f), height(0.0f), fillColor(Color::Transparent), outlineColor(Color::Transparent), value(0.0f), maxValue(0.0f), position(Vector2f(0.0f, 0.0f)) {
    render();
}

Bar::Bar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position)
    : maxWidth(width), width(width), height(height), fillColor(fillColor), outlineColor(outlineColor), value(maxValue), maxValue(maxValue), position(position) {
    render();
}

Bar::Bar(float width, float height, Color fillColor, Color outlineColor, float maxValue, Vector2f position, Sprites spriteType) : 
    maxWidth(width), 
    width(width), 
    height(height), 
    fillColor(fillColor), 
    outlineColor(outlineColor), 
    value(maxValue), maxValue(maxValue), 
    position(position),
    spriteInfo(getSprite(spriteType))
{
    render();
}

const float Bar::getValue() const {
    return value;
}

const float Bar::getMaxWidth() const {
    return maxWidth;
}

void Bar::setMaxValue(const float& newMaxValue)
{
    maxValue = newMaxValue;
}

void Bar::updateValue(const float& newValue) {
    value = newValue;

    bar.setSize(Vector2f((value / maxValue) * maxWidth, height));
}

void Bar::render()
{
    updatePosition(position);

    outline.setSize(Vector2f(maxWidth, height));

    outline.setOutlineThickness(FileMenager::drawsData.outline_thickness);
    outline.setOutlineColor(outlineColor);

    outlineColor.a = FileMenager::drawsData.outline_fill_background_opacity;
    outline.setFillColor(outlineColor);

    bar.setSize(Vector2f(width, height));
    bar.setFillColor(fillColor);
}

void Bar::draw(RenderWindow& window) const {
    window.draw(outline);
    window.draw(bar);
    window.draw(spriteInfo.sprite);
}

void Bar::updatePosition(const Vector2f& position)
{
    outline.setPosition(position);
    bar.setPosition(position);
    spriteInfo.sprite.setPosition(Vector2f{ position.x - (spriteInfo.spriteSize >> 2), position.y });
}