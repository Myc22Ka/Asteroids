#include "Player.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Player::Player() : position(getPropertyValue("player_start_position_x"), getPropertyValue("player_start_position_y")), angle(getPropertyValue("player_start_position_angle")), shape(sf::Quads, 4) {
	auto size = getPropertyValue("player_size");
	
	shape[0].position = sf::Vector2f(size, 0);
	shape[1].position = sf::Vector2f(-size, -size);
	shape[2].position = sf::Vector2f(-size /2, 0);
	shape[3].position = sf::Vector2f(-size, size);

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

void Player::update(float deltaTime) {
	const auto turnSpeed = getPropertyValue("player_turn_speed");
	const auto speed = getPropertyValue("player_speed");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= turnSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += turnSpeed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		float radians = angle * (M_PI / 180.0f);

		position.x += cos(radians) * speed * deltaTime;
		position.y += sin(radians) * speed * deltaTime;
	}
}
