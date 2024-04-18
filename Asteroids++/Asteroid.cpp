#include "Asteroid.h"
#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>
#include <random>
#include <ranges>
#include "Physics.h"

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid() : Entity(sf::Vector2f(), getRandomAngle(), 0, getRandomValue<int>(FileMenager::enemiesData.asteroid_size), sf::Color::Red),
health(100),
healthBar(size, 5, sf::Color::Red, sf::Color::Black, 100)
{
	spriteInfo = getSprite(Sprites::ASTEROID);
	direction = getRandomDirection();
	speed = getRandomValue<float>(FileMenager::enemiesData.asteroid_speed);
	position = getRandomPosition();
	scaleSprite(spriteInfo.sprite, spriteInfo.size, size);

	drawHitboxes();
}

void Asteroid::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	healthBar.draw(window);
	if(WindowBox::hitboxesVisibility) window.draw(shape, transform);
}

void Asteroid::update(float deltaTime) {
	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += sf::Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);
	spriteInfo.spriteLifeTime -= deltaTime;

	const int radius = size >> 1;

	if (position.x < radius) {
		direction.x = abs(direction.x);
	}
	else if (position.x > FileMenager::screenData.size_width - radius) {
		direction.x = -abs(direction.x);
	}

	if (position.y < radius) {
		direction.y = abs(direction.y);
	}
	else if (position.y > FileMenager::screenData.size_height - radius) {
		direction.y = -abs(direction.y);
	}

	healthBar.updateBar(sf::Vector2f{ position.x - radius, position.y + radius });
	healthBar.setCurrentValue(health);

	if (spriteInfo.spriteLifeTime <= 0) {
		spriteInfo.spriteLifeTime = FileMenager::playerData.sprite_cycle_time;
		spriteState = (spriteState + 1) % 2;
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteState);
	}

	collisionDetection();
}

const sf::CircleShape& Asteroid::getVertexShape() const
{
	return shape;
}

const EntityType Asteroid::getEntityType()
{
	return EntityType::TYPE_ASTEROID;
}

void Asteroid::collisionDetection()
{
	for (const auto& entity : EntitiesList::entities) {
		if (entity->getEntityType() == EntityType::TYPE_ASTEROID && entity != this) {
			Asteroid* otherAsteroid = dynamic_cast<Asteroid*>(entity);

			if(otherAsteroid)
				if (physics::intersects(this->position, size >> 1, otherAsteroid->position, otherAsteroid->size >> 1)) {
					const sf::Vector2f normal = physics::normalize(this->position - otherAsteroid->position);

					// Calculate overlap distance
					const float overlap = (this->size + otherAsteroid->size) - physics::distance(this->position, otherAsteroid->position);

					// Separate the asteroids along the collision normal to resolve overlap
					const sf::Vector2f separationVector = normal * overlap * 0.001f;
					this->position += separationVector;
					otherAsteroid->position -= separationVector;

					// Calculate relative velocity along the normal direction
					const sf::Vector2f relativeVelocity = this->speed * physics::normalize(this->direction) - otherAsteroid->speed * physics::normalize(otherAsteroid->direction);
					const float velAlongNormal = physics::dotProduct(relativeVelocity, normal);

					// Calculate total mass
					const float totalMass = this->size + otherAsteroid->size;

					// Calculate the maximum change in direction allowed
					const float maxChangeFactor = 0.7f;
					const float maxChangeMagnitude = maxChangeFactor * velAlongNormal / totalMass;

					// Calculate the change in direction based on momentum conservation, limited by the maximum change
					const sf::Vector2f changeInDirection = std::min(maxChangeMagnitude, std::abs(velAlongNormal)) * normal;

					// Apply change in direction to each asteroid
					this->direction -= changeInDirection;
					otherAsteroid->direction += changeInDirection;
			}
		}
	}
}

const sf::Vector2f Asteroid::getRandomPosition()
{
	const int radius = size >> 1;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xAxis(radius, FileMenager::screenData.size_width - radius);
	std::uniform_real_distribution<float> yAxis(radius, FileMenager::screenData.size_height - radius);

	auto player = std::ranges::find_if(EntitiesList::entities, [](Entity* entity) {
		return entity->getEntityType() == EntityType::TYPE_PLAYER;
		});

	if (player != EntitiesList::entities.end()) {
		sf::Vector2f randomPosition;

		do {
			randomPosition = sf::Vector2f(xAxis(gen), yAxis(gen));
		} while (physics::intersects(randomPosition, radius, (*player)->position, (*player)->size << 1));

		return randomPosition;
	}
}

const float Asteroid::getRandomAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0, 360.0);

	return dist(gen);
}

const sf::Vector2f Asteroid::getRandomDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0, 2.0f * M_PI);

	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}

template<typename T>
inline const T Asteroid::getRandomValue(const T& base)
{
	const double based = base;
		
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(0.75 * based, 1.25 * based);

	return static_cast<T>(dist(gen));
}
