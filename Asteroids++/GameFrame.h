#pragma once
#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include "Page.h"
#include "Wind.h"
#include "DeathScreen.h"
#include "GamePause.h"

using namespace sf;
using namespace std;

class GameFrame : public Page
{
public:
	GameFrame();

	void run(const float& deltaTime, RenderWindow& window) override;
	void navigator(Event& e) override;

private:
	static Wind* wind;
	static GamePause* gamePause;

	static TextField fps;
	Effect fpsDelay;

	void init() override;

	void renderUI(RenderWindow& window);

	void updateWindow(const float& deltaTime, RenderWindow& window);
};

#endif