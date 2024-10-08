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
#include "Enemy.h"

class Enemy;

class Bullet: public Entity {
public:
	Bullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType, Color color);
	Bullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType, Color color, float size);

	virtual void update(float deltaTime) override = 0;
	void render(RenderWindow&) override;
	virtual const EntityType getEntityType() override = 0;
	void collisionDetection() override;

	Vector2f direction;
	float lifeTime;

	static void damageEnemy(Enemy* enemy, bool critHit, Color color);

	void homeToEnemy(float deltaTime);
	Entity* findNearestEnemy() const;
private:
	unordered_set<Entity*> hitEnemies{};

	void enemyHit(Entity* entity);
};

#endif