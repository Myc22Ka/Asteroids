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
	static TextField gameOverText;
	static TextField continueText;

	static void init();
};

#endif