#include "Bullet.h"
#include "Asteroid.h"

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
			const sf::VertexArray& polygon = asteroid->getVertexShape();
			sf::Transform transform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);

			auto n = polygon.getVertexCount() - 1;
			auto intersectionCount = 0;
			sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), position.y);

			for (size_t i = 0; i < n; i++)
			{
				sf::Vector2f p1 = transform.transformPoint(polygon[i].position);
				sf::Vector2f p2 = transform.transformPoint(polygon[(i + 1) % n].position);

				if ((p1.y < position.y && p2.y >= position.y) || (p2.y < position.y && p1.y >= position.y)) {
					float t = (position.y - p1.y) / (p2.y - p1.y);
					float intersectX = p1.x + t * (p2.x - p1.x);

					if (intersectX <= position.x && intersectX <= rayEnd.x) {
						intersectionCount++;
					}
				}
			}

			if (intersectionCount % 2 == 1) {
				lifeTime = 0;
			}
		}
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}
