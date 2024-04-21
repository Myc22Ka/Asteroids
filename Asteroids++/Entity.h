#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "SoundData.h"
#include "SpriteData.h"

enum EntityType {
    TYPE_ENEMY_MULTI_ASTEROID,
    TYPE_ENEMY_SINGLE_ASTEROID,
    TYPE_PLAYER,
    TYPE_BULLET,
    TYPE_EXPLOSION,
    TYPE_PICKUP
};

class Entity : public SpriteData {
public:
    
    Entity(Vector2f position, double angle, int size, Color hitboxColor, SpriteInfo spriteInfo);

    virtual void update(double deltaTime) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    void drawHitboxes();
    void drawHitboxes(const int radius);

    void setSpriteFullCycle(double deltaTime);

    Color hitboxColor;
    Vector2f position;
    CircleShape shape;
    double angle;
    int size;
    double radius;
    SpriteInfo spriteInfo;
};

#endif