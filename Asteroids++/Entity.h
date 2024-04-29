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
    TYPE_BULLET_SINGLE,
    TYPE_EXPLOSION,
    TYPE_PICKUP_1,
    TYPE_PICKUP_2,
    TYPE_PICKUP_3,
    TYPE_PICKUP_4,
    TYPE_PICKUP_PIERCING,
    TYPE_PICKUP_HEART1UP,
    TYPE_PARTICLE,
    TYPE_EVENT_WIND
};

class Entity : public SpriteData {
    bool active = true;
public:
    
    Entity(Vector2f position, double angle, float size, Color hitboxColor, SpriteInfo spriteInfo);

    virtual void update(float deltaTime) = 0;
    virtual void render(RenderWindow& window) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    bool isActive() const;
    void setActive(bool active);

    void drawHitboxes();
    void drawHitboxes(const int radius);

    void setSpriteFullCycle(double deltaTime);
    void setSpriteFullCycle(SpriteInfo& spriteInfo);

    Color hitboxColor;
    Vector2f position;
    CircleShape shape;
    float angle;
    float size;
    float radius;
    SpriteInfo spriteInfo;
};

#endif