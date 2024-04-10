#include "Physics.h"

bool physics::intersects(const sf::Vector2f& point, const float &size ,const sf::Vector2f& circlePosition, const float& size2)
{
	float circleRadius = size + size2;
	float distanceSquared = distance(point, circlePosition);

	return distanceSquared <= circleRadius;
}

float physics::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

std::tuple<float, float, sf::Vector2f, sf::Vector2f> physics::calculateCollision(Asteroid& a1, Asteroid& a2) {
	return std::tuple<float, float, sf::Vector2f, sf::Vector2f>();
}
