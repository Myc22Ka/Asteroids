#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "SoundData.h"
#include "SpriteData.h"

// Enum to represent different types of entities
enum EntityType {
    TYPE_ASTEROID,
    TYPE_PLAYER,
    TYPE_BULLET,
    TYPE_EXPLOSION
};

class Entity : public SpriteData {
public:
    
    Entity(sf::Vector2f position, float angle, int spriteState, int size, sf::Color hitboxColor);

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    void drawHitboxes();

    sf::Color hitboxColor;
    sf::Vector2f position;
    sf::CircleShape shape;
    float angle;
    int size;
    SpriteInfo spriteInfo;
};

#endif