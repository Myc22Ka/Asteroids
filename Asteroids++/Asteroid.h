#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntitiesList.h"
#include "FileMenager.h"

import WindowBox;

class Asteroid : public Entity, public WindowBox {
public:
	Asteroid();

	void render(sf::RenderWindow&) override;
	void update(float) override;

	const sf::Vector2f getRandomDirection();
	const float getRandomVelocity(const float& base);
	const sf::Vector2f getRandomPosition();
	const sf::CircleShape& getVertexShape() const;
	const EntityType getEntityType() override;

	sf::Vector2f position;
	sf::CircleShape shape;
	sf::Vector2f direction;
	float speed;
	int size;
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int spriteState;
	sf::IntRect spriteRects[2];
};

#endif