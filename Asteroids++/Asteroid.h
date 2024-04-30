#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "FileMenager.h"
#include "HealthBar.h"
#include "Bullet.h"
#include <iostream>
#include <random>
#include <ranges>
#include "Physics.h"

class Asteroid : public Entity {
public:
	Asteroid(float health, SpriteInfo spriteInfo);

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	virtual const EntityType getEntityType() override = 0;
	void collisionDetection() override;

	const Vector2f getRandomPosition() const;

	Vector2f direction;
	float speed;
	float health;
	HealthBar healthBar;
};

#endif