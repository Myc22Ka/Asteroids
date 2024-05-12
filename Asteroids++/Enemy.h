#pragma once
#ifndef ENEMY_H
#define ENEMY_H

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
#include "TextField.h"
#include "Effect.h"

class Enemy : public Entity {
	Bar healthBar;
	float health;

public:
	Enemy(float health, float speed, SpriteInfo spriteInfo);

	virtual void render(RenderWindow& window) override;
	virtual void update(float deltaTime) override;
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
	TextField crit;
	Effect critTimer;
};

#endif