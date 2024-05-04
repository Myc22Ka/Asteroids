#pragma once
#ifndef INVADER_H
#define INVADER_H

#include "Asteroid.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class Invader : public Asteroid
{
public:
	Invader();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:
	Vector2f newPosition;
	Vector2f target;
	Effect changePosition;
	Effect shoot;
};

#endif