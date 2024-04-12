#include "Physics.h"

bool physics::intersects(const sf::Vector2f& circlePosition1, const float &radius1 ,const sf::Vector2f& circlePosition2, const float& radius2)
{
	float circleRadiusSum = radius1 + radius2;
	float distanceSquared = distance(circlePosition1, circlePosition2);

	return distanceSquared <= circleRadiusSum;
}

// Funkcja do obliczania d³ugoœci wektora
float physics::length(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Funkcja do normalizacji wektora
sf::Vector2f physics::normalize(const sf::Vector2f& v) {
    float len = length(v);
    if (len != 0) {
        return sf::Vector2f(v.x / len, v.y / len);
    }
    else {
        // Jeœli d³ugoœæ wektora wynosi 0, zwracamy wektor (0, 0)
        return sf::Vector2f(0, 0);
    }
}

float physics::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float physics::distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

std::tuple<float, float, sf::Vector2f, sf::Vector2f> physics::calculateCollision(Asteroid& a1, Asteroid& a2) {
	return std::tuple<float, float, sf::Vector2f, sf::Vector2f>();
}
