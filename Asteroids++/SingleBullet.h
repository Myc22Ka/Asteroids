#pragma once
#ifndef SINGLEBULLET_H
#define SINGLEBULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Score.h"

class SingleBullet : public Bullet {
public:
	SingleBullet(Vector2f position, Vector2f direction, const float& angle);

	const EntityType getEntityType() override;
	void singleAsteroidHit(const int& i) override;
	void multiAsteroidHit(const int& i) override;
};

#endif