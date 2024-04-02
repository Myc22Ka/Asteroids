#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(FileMenager::playerData.bullet_lifetime) {}


void Bullet::update(float deltaTime)
{
	auto bulletSpeed = FileMenager::playerData.bullet_speed;
	lifeTime -= deltaTime;
	position += sf::Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
	if (lifeTime <= 0) {
		EntitiesList::toRemoveList.push_back(
			std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), this));
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}
