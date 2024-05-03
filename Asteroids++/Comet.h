#pragma once
#ifndef COMET_H
#define COMET_H

#include "Asteroid.h"
#include "Entity.h"

using namespace sf;
using namespace std;

class Comet : public Asteroid
{
public:
	Comet();
	
	void render(RenderWindow& window) override;
	void update(float deltaTime) override;
	void collisionDetection() override;
	void destroy() override;

private:

};

#endif