#pragma once
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include "Score.h"

class EnemyBullet : public Bullet {
public:
	EnemyBullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType);

	void update(float deltaTime) override;
	const EntityType getEntityType() override;
};

#endif