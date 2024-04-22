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
	Asteroid(double health, SpriteInfo spriteInfo);

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	virtual const EntityType getEntityType() override = 0;
	void collisionDetection() override;

	const Vector2f getRandomPosition() const;
	const Vector2f getRandomDirection();
	const double getRandomAngle();

	template<typename T>
	const T getRandomValue(const T&);

	Vector2f direction;
	double speed;
	double health;
	HealthBar healthBar;
};

#endif