#pragma once
#ifndef WIND_H
#define WIND_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Score.h"
#include "cmath"
#include "Game.h"
#include "EventHandler.h"

class Wind : public EventHandler {
public:
    Wind();

    void init(const float& deltaTime, RenderWindow& window) override;
    void update(float deltaTime) override;
    const EntityType getEntityType() override;  
    void initParticles() override;

    void remove();
    void forceWind(const float& duration, const float& windLevel, const Vector2f& velocity);

private:
    void activateWind(const float& duration, const float& windLevel, const Vector2f& velocity);
    void stopWind();

    const Vector2f getRandomPosition() const;

    void wrapLine(Vertex& vertex1, Vertex& vertex2) const;
    void resetParticlePositions();

    Effect wind;

    float windSpeed;
    float fullWindDuration;
    float windLevel;
    float lineWidth;
    float lineHeight;
    Vector2f velocity;
};

#endif