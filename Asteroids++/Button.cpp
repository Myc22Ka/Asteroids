#include "Button.h"

Button::Button(Sprites spriteType, TextField text, Vector2f position) : fill(VertexArray(Quads, 4)), spriteInfo(SpriteData::getSprite(spriteType)), text(text)
{
	initFillRect(position);

	setFillColor({ 0, 0, 0, 200 });
}

void Button::setFillColor(const Color& color)
{
	for (size_t i = 0; i < fill.getVertexCount(); i++)
		fill[i].color = color;
}

TextField& Button::getText()
{
	return text;
}

void Button::draw(RenderWindow& window) const
{
	window.draw(fill);
	window.draw(spriteInfo.sprite);
	text.draw(window);
}

void Button::initFillRect(const Vector2f& position)
{
    float size = 200.0f;

    float halfSize = size / 2.0f;
    Vector2f topLeftCorner = position - Vector2f(halfSize, halfSize);

    fill[0].position = topLeftCorner;
    fill[1].position = topLeftCorner + Vector2f(size, 0.0f);
    fill[2].position = topLeftCorner + Vector2f(size, size);
    fill[3].position = topLeftCorner + Vector2f(0.0f, size);

    float textX = topLeftCorner.x + (size - text.getText().getLocalBounds().width) / 2.0f;
    float textY = topLeftCorner.y + (size - text.getText().getLocalBounds().height) / 1.5f;

    float spriteX = topLeftCorner.x + halfSize;
    float spriteY = topLeftCorner.y + (size - spriteInfo.sprite.getLocalBounds().height) / 2.5f;

    text.setTextPosition({ textX, textY });

    spriteInfo.sprite.setPosition({ spriteX, spriteY });
}
