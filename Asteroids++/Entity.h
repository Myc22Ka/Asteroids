#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Sound.h"

// Enum to represent different types of entities
enum EntityType {
    TYPE_ASTEROID,
    TYPE_PLAYER,
    TYPE_BULLET
};

enum class Sprites {
    SHIP,
    ASTEROID,
    BULLET
};

class Entity {
public:
    
    Entity(sf::Vector2f position, float angle, int spriteState, int size, sf::Color hitboxColor);

    ~Entity();

    virtual void update(float) = 0;
    virtual void render(sf::RenderWindow&) = 0;
    virtual const EntityType getEntityType() = 0;
    virtual void collisionDetection() = 0;

    void drawSprite(Sprites, const int&);
    void setSprite(const int&);
    void drawHitboxes();

    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect* spriteRects;
    float spriteLifeTime;
    int spriteState;

    sf::Color hitboxColor;
    sf::Vector2f position;
    sf::CircleShape shape;
    float angle;
    int size;

};

#endif