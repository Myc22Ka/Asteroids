#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "FileMenager.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "SoundData.h"

struct PlayerStats {
	double speed;
	double turnSpeed;
	double lifes;

	double shootOffset;
	double accurancy;
	double bulletSize;
	double bulletDamage;
	double bulletSpeed;

	bool piercing;
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
	static double dashTimer;
private:
	SpriteInfo shield;

	void resetPlayerStats();
	void setPlayerStats();
	void dashAbility(const double&);
	double shootTimer;
	bool isDashing = false;
	double invincibilityFrames;
};

#endif