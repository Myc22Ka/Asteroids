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

    void activateWind(float duration, float speed, float direction);
private:
    void wrapQuad(Vertex& vertex1, Vertex& vertex2, Vertex& vertex3, Vertex& vertex4) const;
    void resetParticlePositions();

    VertexArray particles;

    float windDelay;
    float windSpeed;
    float windDirection;
    bool windActive;
    bool wasWindActive;
    float windDuration;
    int windLevel;
    float lineWidth;
    float lineHeight;
};

#endif