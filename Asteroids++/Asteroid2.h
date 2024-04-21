#pragma once
#ifndef ASTEROID2_H
#define ASTEROID2_H

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

class Asteroid2 : public Entity {
public:
	Asteroid2();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	const CircleShape& getVertexShape() const;

	const Vector2f getRandomPosition() const;
	const Vector2f getRandomDirection();
	const float getRandomAngle();

	template<typename T>
	const T getRandomValue(const T&);

	Vector2f direction;
	float speed;
	int health;
private:

	int spriteState;
	HealthBar healthBar;
};

#endif