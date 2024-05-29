#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "Enemy.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class Tower : public Enemy
{
public:
	Tower();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:
	Effect shoot;
	Effect changePosition;
	int shootCounter;
};

#endif