#pragma once
#ifndef WIND_H
#define WIND_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Score.h"

class Wind : public Entity {
public:
    Wind();

    const Vector2f getRandomPosition() const;

    void render(RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;
private:
    SpriteInfo collected;
    double lifeTime;
};

#endif