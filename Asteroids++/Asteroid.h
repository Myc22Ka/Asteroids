#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "FileMenager.h"
#include "Bar.h"
#include "Bullet.h"
#include <iostream>
#include <random>
#include <ranges>
#include "Physics.h"

class Asteroid : public Entity {
	Bar healthBar;
	float health;

public:
	Asteroid(float health, float speed, SpriteInfo spriteInfo);

	virtual void render(RenderWindow& window) override = 0;
	virtual void update(float deltaTime) override = 0;
	virtual const EntityType getEntityType() override;
	virtual void collisionDetection() override = 0;
	virtual void destroy() = 0;

	void bounceCollisionDetection();
	const Vector2f getRandomPosition() const;

	const Bar& getHealthBar() const;
	void updateHealthBar();

	const float getHealth();
	void updateHealth(const float& newValue);

	float speed;
	Vector2f direction;
};

#endif