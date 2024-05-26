#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "TextField.h"
#include "Player.h"
#include "Page.h"

using namespace sf;
using namespace std;

class GameOver : public Page
{
public:
	GameOver();

	TextField playerNameText;

	void run(const float& deltaTime, RenderWindow& window) override;
	void navigator(Event& e) override;

private:
	void init() override;
	void drawPlayerName(RenderWindow& window);

	TextField gameOver;
	TextField underscore;

	string playerName;
};

#endif