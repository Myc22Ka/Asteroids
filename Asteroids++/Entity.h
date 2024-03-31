#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
	public:
		Entity(sf::Vector2f, float);
		virtual void update(float) = 0;
		virtual void render(sf::RenderWindow&) = 0;

		sf::Vector2f position;
		float angle;
};

#endif