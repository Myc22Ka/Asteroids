#pragma once
#ifndef PICKUP_H
#define PICKUP_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Player.h"
#include "Score.h"

class Pickup : public Entity {
public:
    Pickup(Vector2f position, SpriteInfo spriteInfo);

    void render(RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;
private:
    SpriteInfo collected;
    double lifeTime;
};

#endif