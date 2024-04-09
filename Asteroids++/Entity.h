#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Sound.h"

struct Size {
    float width;
    float height;
};

// Enum to represent different types of entities
enum EntityType {
    TYPE_ASTEROID,
    TYPE_PLAYER,
    TYPE_BULLET
};

class Entity {
public:
    Entity(sf::Vector2f, float);
    virtual void update(float) = 0;
    virtual void render(sf::RenderWindow&) = 0;
    virtual const Size getEntitySize() = 0;
    virtual const EntityType getEntityType() = 0;
    void playSound(Names name);

    sf::Vector2f position;
    float angle;
};

#endif