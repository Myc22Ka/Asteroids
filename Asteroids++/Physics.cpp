#include "Physics.h"

bool physics::intersects(const Vector2f& circlePosition1, const float &radius1 ,const Vector2f& circlePosition2, const float& radius2)
{
	float circleRadiusSum = radius1 + radius2;
	float distanceSquared = distance(circlePosition1, circlePosition2);

	return distanceSquared <= circleRadiusSum;
}

// Funkcja do obliczania d³ugoœci wektora
float physics::length(const Vector2f& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

// Funkcja do normalizacji wektora
Vector2f physics::normalize(const Vector2f& v) {
    float len = length(v);
    if (len != 0) {
        return Vector2f(v.x / len, v.y / len);
    }
    else {
        // Jeœli d³ugoœæ wektora wynosi 0, zwracamy wektor (0, 0)
        return Vector2f(0, 0);
    }
}

Vector2f physics::calculateDirection(const Vector2f& startPos, const Vector2f& targetPos) {
	Vector2f direction = targetPos - startPos;
	// Normalize the direction vector
	float length = physics::magnitude(direction);
	if (length != 0) {
		direction /= length;
	}
	return direction;
}

float physics::magnitude(const Vector2f& vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float physics::dotProduct(const Vector2f& v1, const Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float physics::distance(const Vector2f& p1, const Vector2f& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

pair<Vector2f, Vector2f> physics::bounceDirection(const Asteroid* thisAsteroid, const Asteroid* otherAsteroid,const float& separationDistance)
{
	const Vector2f normal = physics::normalize(thisAsteroid->position - otherAsteroid->position);

	// Calculate overlap distance
	const float overlap = (thisAsteroid->size + otherAsteroid->size) - physics::distance(thisAsteroid->position, otherAsteroid->position);

	// Separate the asteroids along the collision normal to resolve overlap
	const Vector2f separationVector = normal * overlap * separationDistance;

	// Calculate relative velocity along the normal direction
	const Vector2f relativeVelocity = static_cast<float>(thisAsteroid->speed) * physics::normalize(thisAsteroid->direction) - static_cast<float>(otherAsteroid->speed) * physics::normalize(otherAsteroid->direction);
	const float velAlongNormal = physics::dotProduct(relativeVelocity, normal);

	// Calculate total mass
	const float totalMass = thisAsteroid->size + otherAsteroid->size;

	// Calculate the maximum change in direction allowed
	const float maxChangeFactor = 0.7f;
	const float maxChangeMagnitude = maxChangeFactor * velAlongNormal / totalMass;

	// Calculate the change in direction based on momentum conservation, limited by the maximum change
	return pair(min(maxChangeMagnitude, abs(velAlongNormal)) * normal, separationVector);
}
