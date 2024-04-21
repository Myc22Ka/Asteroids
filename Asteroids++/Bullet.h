#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"
#include "Game.h"
#include "Player.h"
#include "Explosion.h"

class Bullet: public Entity {
public:
	Bullet(Vector2f, Vector2f, const float&);

	void update(double deltaTime) override;
	void render(RenderWindow&) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;



	int damage;
private:
	
	void singleAsteroidHit(const int& i);

	void multiAsteroidHit(const int& i);

	Vector2f direction;
	float lifeTime;
};

#endif