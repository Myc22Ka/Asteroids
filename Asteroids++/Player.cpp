#include "Player.h"

Player::Player() : position(500, 500), angle(45), shape(sf::Quads, 4) {
	shape[0].position = sf::Vector2f(0, -size);
	shape[1].position = sf::Vector2f(-size, size);
	shape[2].position = sf::Vector2f(0, size/2);
	shape[3].position = sf::Vector2f(size, size);

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		shape[i].color = sf::Color::White;
	}
}

void Player::draw(sf::RenderWindow& window)
{
	sf::Transform transform;
	transform.translate(position).rotate(angle);
	window.draw(shape, transform);
}
