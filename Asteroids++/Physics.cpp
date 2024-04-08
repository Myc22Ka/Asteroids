#include "Physics.h"

bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon)
{
	auto n = polygon.getVertexCount() - 1;
	auto intersectionCount = 0;
	sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

	for (size_t i = 0; i < n; i++)
	{
		sf::Vector2f p1 = polygon[i].position;
		sf::Vector2f p2 = polygon[(i + 1) % n].position;

		if ((p1.y < point.y && p2.y >= point.y) || (p2.y < point.y && p1.y >= point.y)) {
			float t = (point.y - p1.y) / (p2.y - p1.y);
			float intersectX = p1.x + t * (p2.x - p1.x);

			if (intersectX <= point.x && intersectX <= rayEnd.x) {
				intersectionCount++;
			}
		}
	}

	return intersectionCount % 2 == 1;
}

sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform)
{
	sf::VertexArray transformed = polygon;

	for (size_t i = 0; i < transformed.getVertexCount(); i++) {
		transformed[i].position = transform.transformPoint(transformed[i].position);
	}

	return transformed;
}
