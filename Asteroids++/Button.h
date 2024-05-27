#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "SpriteData.h"
#include "TextField.h"

using namespace sf;
using namespace std;

class Button
{
public:
	Button(Sprites spriteType, TextField text, Vector2f position);

	void setFillColor(const Color& color);
	TextField& getText();

	void draw(RenderWindow& window) const;

	void initFillRect(const Vector2f& position);

private:

	VertexArray fill;
	SpriteInfo spriteInfo;
	TextField text;
};
#endif