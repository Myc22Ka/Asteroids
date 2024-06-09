#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Score.h"

class Particle : public Entity {
public:
    Particle(Vector2f position, float angle, Sprites sprites, Color color, double lifeTime, bool oneCycleLife);
    Particle(Vector2f position, float angle, Sprites sprites, Color color, double lifeTime);
    Particle(Vector2f position, float angle, Sprites sprites, Color color, double lifeTime, float size);

    void render(RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;

private:
    double lifeTime;
    bool oneCycleLife = false;
};

#endif