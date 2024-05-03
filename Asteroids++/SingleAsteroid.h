#pragma once
#ifndef SINGLEASTEROID_H
#define SINGLEASTEROID_H

#include "Asteroid.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class SingleAsteroid : public Asteroid
{
public:
	SingleAsteroid();
	SingleAsteroid(Vector2f position, Vector2f direction);

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:
};
#endif