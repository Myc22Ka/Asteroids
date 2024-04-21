#pragma once
#ifndef PICKUP_H
#define PICKUP_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Player.h"

class Pickup : public Entity {
public:
    Pickup(Vector2f position);

    void render(RenderWindow& window) override;
    void update(double deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;
private:
    double lifeTime;
};

#endif