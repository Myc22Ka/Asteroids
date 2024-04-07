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
	const Size getEntitySize() override;

	const sf::Vector2f getRandomDirection();
	const float getRandomVelocity(const float& base);
	const sf::Vector2f getRandomPosition();
	const sf::VertexArray& getVertexShape() const;

	sf::Vector2f position;
private:
	sf::VertexArray shape;
	sf::Vector2f direction;
	const float speed;
};

#endif