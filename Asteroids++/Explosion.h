#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"
#include "Game.h"
#include <random>

class Explosion : public Entity {
public:
	Explosion(Vector2f position, int size);

	void update(float deltaTime) override;
	void render(RenderWindow& window) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

private:
	Sprites setRandomSprite();
	int spriteState;
};

#endif