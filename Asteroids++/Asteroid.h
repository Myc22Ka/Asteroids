#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntitiesList.h"
#include "FileMenager.h"
#include "HealthBar.h"

import WindowBox;

class Asteroid : public Entity, public WindowBox {
public:
	Asteroid();

	void render(sf::RenderWindow&) override;
	void update(float) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	const sf::CircleShape& getVertexShape() const;

	const sf::Vector2f getRandomDirection();
	const sf::Vector2f getRandomPosition();
	const float getRandomAngle();

	template<typename T>
	const T getRandomValue(const T&);

	sf::Vector2f direction;
	float speed;
	int health;
private:
	int spriteState;
	HealthBar healthBar;
};

#endif