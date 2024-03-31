#include "Player.h"
#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Player::Player() : 
	Entity(sf::Vector2f(getValueFromProperty("player_start_position_x"), getValueFromProperty("player_start_position_y")), getValueFromProperty("player_start_position_angle")),
	shape(sf::Quads, 4) 
{
	auto size = getValueFromProperty("player_size");

	
	shape[0].position = sf::Vector2f(size, 0);
	shape[1].position = sf::Vector2f(-size, -size);
	shape[2].position = sf::Vector2f(-size /2, 0);
	shape[3].position = sf::Vector2f(-size, size);

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		shape[i].color = sf::Color::White;
	}
}

void Player::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(shape, transform.translate(position).rotate(angle));
}

void Player::update(float deltaTime) {
	const auto turnSpeed = getValueFromProperty("player_turn_speed");
	const auto speed = getValueFromProperty("player_speed");

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		float radians = angle * (M_PI / 180.0f);
		EntitiesList::entities.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
	}
}
