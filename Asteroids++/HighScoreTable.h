#pragma once
#ifndef HIGHSCORETABLE_H
#define HIGHSCORETABLE_H

#include "TextField.h"
#include "Player.h"
#include "Page.h"

using namespace sf;
using namespace std;

class HighScoreTable : public Page
{
public:
	HighScoreTable();

	void run(const float& deltaTime, RenderWindow& window);

private:
	void init();

	TextField highscoreText;
};

#endif