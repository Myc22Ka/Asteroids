#pragma once
#include <SFML/Graphics.hpp>

namespace physics {
	bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);
	sf::VertexArray getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);
}
