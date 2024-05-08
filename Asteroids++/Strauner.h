#pragma once
#ifndef STRAUNER_H
#define STRAUNER_H

#include "Enemy.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class Strauner : public Enemy
{
public:
	Strauner();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:
	Vector2f newPosition;
	Vector2f target;
	Effect changePosition;
	Effect shoot;

	float hue;
};

#endif