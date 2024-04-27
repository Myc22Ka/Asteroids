#pragma once
#ifndef SINGLEBULLET_H
#define SINGLEBULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Score.h"

class SingleBullet : public Bullet {
public:
	SingleBullet(Vector2f position, Vector2f direction, float& angle);

	const EntityType getEntityType() override;
};

#endif