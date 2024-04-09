#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Score.h"
#include "Sound.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(FileMenager::playerData.bullet_lifetime) {}

const Size Bullet::getEntitySize()
{
	return Size();
}


void Bullet::update(float deltaTime)
{
	auto bulletSpeed = FileMenager::playerData.bullet_speed;
	lifeTime -= deltaTime;
	position += sf::Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
	if (lifeTime <= 0) {
		EntitiesList::toRemoveList.push_back(
			std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), this));
	}

	for (size_t i = 0; i < EntitiesList::entities.size(); i++)
	{
		if (typeid(*EntitiesList::entities[i]) == typeid(Asteroid)) {
			Asteroid* asteroid = dynamic_cast<Asteroid*>(EntitiesList::entities[i]);
			sf::Transform transform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);

			if (physics::intersects(position, 
				physics::getTransformed(asteroid->getVertexShape(), transform))) {
				lifeTime = 0;
				EntitiesList::toRemoveList.push_back(
					std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), asteroid));
				Score::score += 10;

				playSound(Names::EXPLOSION);
			}
		}
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}
