#pragma once
#ifndef WIND_H
#define WIND_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Score.h"
#include "cmath"
#include "Game.h"

class Wind : public Entity {
public:
    Wind();

    const Vector2f getRandomPosition() const;

    void render(RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;
    void collisionDetection() override;

    void activateWind(const float& duration, const float& windLevel, const Vector2f& velocity);
    void stopWind();

    void init(const float& deltaTime, RenderWindow& window);

private:
    void wrapLine(Vertex& vertex1, Vertex& vertex2) const;
    void resetParticlePositions();

    VertexArray particles;
    Effect wind;

    float windSpeed;
    float fullWindDuration;
    float windLevel;
    float lineWidth;
    float lineHeight;
    Vector2f velocity;
};

#endif