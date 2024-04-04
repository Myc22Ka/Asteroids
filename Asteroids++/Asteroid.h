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
	Asteroid(const sf::Vector2f&, const float&);

	void render(sf::RenderWindow&) override;
	void update(float) override;
	const Size getEntitySize() override;

	static sf::Vector2f getRandomDirection();
	static const float getRandomVelocity(const float& base);

private:
	sf::VertexArray shape;
	sf::Vector2f direction;
	const float speed;
};

#endif