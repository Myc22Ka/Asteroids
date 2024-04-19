#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "FileMenager.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "SoundData.h"

class Player: public Entity {
public:
	Player();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	static float dashTimer;
private:
	void dashAbility(const float&);
	float shootTimer;
	bool isDashing = false;
	float speed;
	int spriteState;
};

#endif