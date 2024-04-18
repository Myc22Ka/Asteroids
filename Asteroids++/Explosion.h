#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"

import WindowBox;

class Explosion : public Entity {
public:
	Explosion(sf::Vector2f position, int size);

	void update(float) override;
	void render(sf::RenderWindow&) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

private:
	Sprites setRandomSprite();
	int spriteState;
};

#endif