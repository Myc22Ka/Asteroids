#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "FileMenager.h"
#include "Bar.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "SoundData.h"
#include "Effect.h"
#include "Physics.h"

struct BulletType {
	bool piercing;
	bool homing;
};

struct PlayerStats {
	float speed;
	float turnSpeed;
	float lifes;

	float time;

	float shootOffset;
	float accurancy;
	float bulletSize;
	float bulletDamage;
	float bulletSpeed;

	BulletType bulletType;

	Effect scoreTimes5;
	Effect scoreTimes2;
	Effect shield;
	Effect drunkMode;
};

class Player : public Entity {
public:
	Player();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	static Sprites getPlayerBulletSprite();

	static PlayerStats playerStats;
	static float dashTimer;
private:
	SpriteInfo shieldSprite;

	bool dead;
	Effect delay;

	void updateStatsbars(const float& deltaTime);
	void updatePosition(const float& deltaTime);
	void setPlayerStats();
	void dashAbility(const float&);
	float shootTimer;
	bool isDashing = false;
	float invincibilityFrames;
};

#endif