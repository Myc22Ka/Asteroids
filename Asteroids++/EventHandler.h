#pragma once
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Effect.h"

using namespace sf;

class EventHandler
{
public:
	EventHandler(VertexArray particles);

	virtual void update(float deltaTime) = 0;
	virtual const EntityType getEntityType() = 0;
	virtual void init(const float& deltaTime, RenderWindow& window) = 0;
	virtual void initParticles() = 0;

	void render(RenderWindow& window) const;

	VertexArray particles;
private:
};

#endif