#pragma once
#ifndef MULTIASTEROID_H
#define MULTIASTEROID_H

#include "Enemy.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class MultiAsteroid : public Enemy
{
public:
	MultiAsteroid();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:
};
#endif