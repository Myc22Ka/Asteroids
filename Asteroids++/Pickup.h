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
    Pickup(Vector2f position);
    Pickup(Vector2f position, Sprites spriteType);

    void render(RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;

    const static Sprites getRandomDrop(const map<double, Sprites>& group);

    const static Sprites getRandomFromGroup(const vector<Sprites>& group);

    const static map<double, Sprites> boosters;
    const static vector<Sprites> modifiers;
    const static vector<Sprites> bulletTypes;
private:

    SpriteInfo collected;
    double lifeTime;
};

#endif