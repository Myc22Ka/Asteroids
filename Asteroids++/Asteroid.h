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
	Asteroid(sf::Vector2f);

	void render(sf::RenderWindow&) override;
	void update(float) override;
private:
	sf::VertexArray shape;
	sf::Vector2f direction;
};

#endif