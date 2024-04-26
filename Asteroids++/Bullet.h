#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"
#include "Game.h"
#include "Player.h"
#include "Explosion.h"
#include <unordered_set>

class Bullet: public Entity {
public:
	Bullet(Vector2f position, Vector2f direction, const float& angle);

	void update(float deltaTime) override;
	void render(RenderWindow&) override;
	virtual const EntityType getEntityType() override = 0;
	void collisionDetection() override;

	void spawnPickup(const Vector2f& position);

	template<typename T>
	void asteroidHit(const int& i);

	void destroySingleAsteroid(const int& i);
	void destroyMultiAsteroid(const int& i);

	Vector2f direction;
	float lifeTime;

	unordered_set<int> hitAsteroids{};
private:
	static bool piercing;
};

#endif