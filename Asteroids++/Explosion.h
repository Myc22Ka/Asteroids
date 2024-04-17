#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"
#include "SpriteData.h"

import WindowBox;

class Explosion : public Entity, public SpriteData {
public:
	Explosion(sf::Vector2f position);

	void update(float) override;
	void render(sf::RenderWindow&) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

private:
	int spriteState;
};

#endif