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
	double shootOffset;
};

class Player: public Entity {
public:
	Player();

	void render(RenderWindow& window) override;
	void update(double deltaTime) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	static PlayerStats playerStats;
	static double dashTimer;
private:
	void setPlayerStats();
	void dashAbility(const double&);
	double shootTimer;
	bool isDashing = false;
	double speed;
};

#endif