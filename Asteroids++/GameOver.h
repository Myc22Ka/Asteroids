#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "TextField.h"
#include "Player.h"

using namespace sf;
using namespace std;

class GameOver
{
public:
	static TextField playerNameText;

	static void init();
	static void enterPlayerName(Event& e);
	static void draw(RenderWindow& window);
	static void update(const float& deltaTime);

	static void drawPlayerName(RenderWindow& window);

private:
	static TextField gameOver;
	static TextField underscore;

	static string playerName;
	static Texture texture;
	static Sprite background;
};

#endif