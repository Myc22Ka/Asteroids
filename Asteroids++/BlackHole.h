#pragma once
#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "Enemy.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class BlackHole : public Enemy
{
public:
	BlackHole();

	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void devour(Entity* entity);
	void destroy() override;

private:

};

#endif