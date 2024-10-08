#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "SoundData.h"
#include "SpriteData.h"

enum EntityType {
    TYPE_ENEMY,
    TYPE_PLAYER,
    TYPE_BULLET_SINGLE,
    TYPE_ENEMY_BULLET,
    TYPE_EXPLOSION,
    TYPE_PICKUP,
    TYPE_PARTICLE,
    TYPE_EVENT_WIND,
    TYPE_EVENT_DEATHSCREEN
};

class BlackHole;

class Entity : public SpriteData {
    bool active = true;
    BlackHole* spiralingTarget;
public:
    
    Entity(Vector2f position, float angle, float size, Color hitboxColor, SpriteInfo spriteInfo);

    virtual void update(float deltaTime);
    virtual void render(RenderWindow& window) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    bool isActive() const;
    void setActive(const bool& active);

    const Sprites getSpriteType() const;

    void drawHitboxes();
    void drawHitboxes(const float& radius);

    void setSpriteFullCycle(const double& deltaTime);
    void setSpriteFullCycle(SpriteInfo& spriteInfo);

    void startSpiraling(BlackHole* blackHole);

    Color hitboxColor;
    Vector2f position;
    CircleShape shape;
    bool spiraling;
    float angle;
    float size;
    float radius;
    SpriteInfo spriteInfo;
};

#endif