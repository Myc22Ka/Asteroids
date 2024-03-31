#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : shape(1.0f), direction(direction), Entity(position, 0.0f) {}


void Bullet::update(float deltaTime)
{
	auto bulletSpeed = getValueFromProperty("player_bullet_speed");
	position += sf::Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}
