#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "FileMenager.h"
#include "EntitiesList.h"
#include "Player.h"
#include "Explosion.h"

class Bullet: public Entity {
public:
	Bullet(sf::Vector2f, sf::Vector2f, const float&);

	void update(float) override;
	void render(sf::RenderWindow&) override;
	const EntityType getEntityType() override;
	void collisionDetection() override;

	int damage;
private:
	sf::Vector2f direction;
	float lifeTime;

	friend Player;
	friend Explosion;
};

#endif