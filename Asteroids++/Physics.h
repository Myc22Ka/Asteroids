#pragma once
#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <tuple>

namespace physics {
	bool intersects(const sf::Vector2f& point, const float& size, const sf::Vector2f& circlePosition, const float& size2);
	float length(const sf::Vector2f& v);
	sf::Vector2f normalize(const sf::Vector2f& v);
	float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	std::tuple<float, float, sf::Vector2f, sf::Vector2f> calculateCollision(Asteroid& a1, Asteroid& a2);
}
