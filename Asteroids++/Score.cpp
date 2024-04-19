#include "Score.h"
#include <iostream>

size_t Score::score{};
Text Score::scoreText{};
Font Score::font{};

void Score::init()
{
	if (!font.loadFromFile("./assets/font.ttf")) {
		cout << "Error: Could not open file: font.ttf\n";
		return;
	}

	scoreText.setFont(font);
	scoreText.setPosition(Vector2f(30, 20));
	scoreText.setCharacterSize(48);
}
