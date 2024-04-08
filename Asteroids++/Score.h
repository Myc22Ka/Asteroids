#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

class Score
{
public:
	static size_t score;
	static sf::Text scoreText;
	static sf::Font font;
	
	static void init();
};

#endif 
