#pragma once
#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Effect.h"
#include "EventHandler.h"

class DeathScreen: public EventHandler {
public:
	DeathScreen();

	void update(float deltaTime) override;
	const EntityType getEntityType() override;
	void init(const float& deltaTime, RenderWindow& window) override;
	void initParticles() override;

	static void activateDeathScreen(const float& duration);

	static bool isScreenOver();

	static void setDelay(const float& duration);

private:
	void resetPosition();
	
	static Effect delay;
	static Effect death;

	float velocity;
};

#endif
