#pragma once
#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class TextField
{
public:
	TextField(int size);
	TextField(string content, int size);

	void setTextPosition(const Vector2f& position);
	void setTextCenterX(const float& y);
	void setTextCenterY(const float& x);

	void setText(const string& text);
	void setSize(const int size);
	void setLetterSpacing(const double spacing);
	Text& getText();

	void setColorText(const Color& color);

	static void loadFont();
private:
	Text text;
	static Font font;
	int size;
};
#endif