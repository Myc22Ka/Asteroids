#pragma once
#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <random>

using namespace std;

class Asteroid;

namespace physics {
	bool intersects(const Vector2f& point, const float& size, const Vector2f& circlePosition, const float& size2);
	float length(const Vector2f& v);
	Vector2f normalize(const Vector2f& v);
	Vector2f calculateDirection(const Vector2f& startPos, const Vector2f& targetPos);
	float magnitude(const Vector2f& vec);
	float dotProduct(const Vector2f& v1, const Vector2f& v2);
	float distance(const Vector2f& p1, const Vector2f& p2);
	pair<Vector2f, Vector2f> bounceDirection(const Asteroid* thisAsteroid, const Asteroid* otherAsteroid, const float& separationDistance);

	float getRandomFloatValue(const float& base);
	const Vector2f getRandomDirection();
	const float getRandomAngle();
}
