#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"

class Bullet: public Entity {
	sf::CircleShape shape;
	sf::Vector2f direction;
public:
	Bullet(sf::Vector2f, sf::Vector2f);
	void update(float) override;
	void render(sf::RenderWindow&) override;
};

#endif