#pragma once
#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Effect.h"

class DeathScreen {
public:
	DeathScreen();

	static void render(RenderWindow& window);
	static void update(float deltaTime);

	static void activateDeathScreen(const float& duration);

	static bool isScreenOver();

	static void setDelay(const float& duration);

	void init(const float& deltaTime, RenderWindow& window);
private:
	static void resetPosition();
	
	static Effect delay;
	static VertexArray particles;
	static Effect death;
};

#endif
