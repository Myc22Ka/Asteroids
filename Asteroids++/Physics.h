#pragma once
#include <SFML/Graphics.hpp>
#include "Asteroid.h"

namespace physics {
	bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);
	bool intersects(const Asteroid& asteroid1, const Asteroid& asteroid2);
	bool intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2);
	
	sf::VertexArray getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);
}
