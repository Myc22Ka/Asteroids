#include "Score.h"
#include <iostream>

size_t Score::score{0};
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

void Score::addScore(const size_t& value)
{
	score += (value * (Player::playerStats.scoreTimes2.isEffectActive() ? 2 : Player::playerStats.scoreTimes5.isEffectActive() ? 5 : 1));
}
