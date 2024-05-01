#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;
using namespace std;

class Score
{
public:
	static size_t score;
	static Text scoreText;
	static Font font;

	static void init();
	static void addScore(const size_t& value);
};

#endif 
