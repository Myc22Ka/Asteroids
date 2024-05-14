#include "TextField.h"
#include "WindowBox.h"

Font TextField::font{};

TextField::TextField(int size) : size(size) {

	text.setFont(TextField::font);
	text.setCharacterSize(size);
}

TextField::TextField(string content, int size) : size(size) {
	text.setFont(TextField::font);
	setText(content);
}

void TextField::setTextPosition(const Vector2f& position) {
	text.setPosition(position);
}

void TextField::setTextCenterX(const float& y) {
	text.setPosition(Vector2f(float((WindowBox::getVideoMode().width >> 1) - (text.getLocalBounds().width / 2.0f)), y));
}

void TextField::setTextCenterY(const float& x) {
}

void TextField::setText(const string& text) {
	this->text.setString(text);
}

void TextField::setSize(const int size) {
	text.setCharacterSize(size);
}

void TextField::setLetterSpacing(const double spacing) {
	text.setLetterSpacing(spacing);
}

Text& TextField::getText()
{
	return text;
}

void TextField::setColorText(const Color& color) {
	text.setFillColor(color);
}

void TextField::loadFont()
{
	if (!font.loadFromFile("./assets/font.otf")) {
		cout << "Error: Could not open file: font.otf\n";
		return;
	}
}
