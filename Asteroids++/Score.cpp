#include "Score.h"
#include <iostream>

size_t Score::score{};
sf::Text Score::scoreText{};
sf::Font Score::font{};

void Score::init()
{
	font.loadFromFile("./assets/font.ttf");

	if (!font.loadFromFile("./assets/font.ttf")) {
		std::cout << "Error: Could not open file: font.ttf\n";
		return;
	}

	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(30, 20));
	scoreText.setCharacterSize(48);
}
