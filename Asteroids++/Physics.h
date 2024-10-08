#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <random>
#include <ranges>

using namespace std;

class Enemy;

namespace physics {
	bool intersects(const Vector2f& point, const float& size, const Vector2f& circlePosition, const float& size2);
	float length(const Vector2f& v);
	Vector2f normalize(const Vector2f& v);

	Vector2f calculateDirection(const Vector2f& startPos, const Vector2f& targetPos);
	Vector2f calculateDirection(const float& angle);
	Vector2f calculateDirection(const float& angle, const float& spreadAngle);

	float floatToAngle(const float& value);
	float angleToRadians(const float& angle);

	float magnitude(const Vector2f& vec);
	float dotProduct(const Vector2f& v1, const Vector2f& v2);
	float distance(const Vector2f& p1, const Vector2f& p2);
	pair<Vector2f, Vector2f> bounceDirection(const Enemy* thisEnemy, const Enemy* otherEnemy, const float& separationDistance);

	float getRandomFloatValue(const float& base);
	float getRandomFloatValue(const float& base, const float& range);
	float getRandomOpacity();
	const Vector2f getRandomDirection();
	const Vector2f getRandomPosition(const float& size);
	const float getRandomAngle();

	const bool rollDice(const double chance);
	const double rollDice();

	const float getPI();
}
