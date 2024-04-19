#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "SoundData.h"
#include "SpriteData.h"

enum EntityType {
    TYPE_ASTEROID,
    TYPE_PLAYER,
    TYPE_BULLET,
    TYPE_EXPLOSION
};

class Entity : public SpriteData {
public:
    
    Entity(Vector2f position, float angle, int spriteState, int size, Color hitboxColor);

    virtual void update(float deltaTime) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    void drawHitboxes();

    Color hitboxColor;
    Vector2f position;
    CircleShape shape;
    float angle;
    int size;
    double radius;
    SpriteInfo spriteInfo;
};

#endif