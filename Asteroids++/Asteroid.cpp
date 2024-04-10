#include "Asteroid.h"
#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>
#include <random>
#include "Physics.h"

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid() :
		size((int)FileMenager::enemiesData.asteroid_size >> 1),
		Entity(sf::Vector2f(0, 0), 0),
		shape(FileMenager::enemiesData.asteroid_size)
{
	direction = Asteroid::getRandomDirection();
	position = Asteroid::getRandomPosition();
	speed = Asteroid::getRandomVelocity(FileMenager::enemiesData.asteroid_speed);

	sf::Vector2f center(size, size);

	shape.setRadius(size);

	shape.setOrigin(center);

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);

	if (!texture.loadFromFile("./assets/asteroid.png")) {
		std::cout << "Error: Could not load sprite : ";
		return;
	}

	const auto spriteSize = size << 1;

	spriteRects[0] = sf::IntRect(0, 0, spriteSize, spriteSize);

	sprite.setTexture(texture);
	sprite.setTextureRect(spriteRects[0]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
}

void Asteroid::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(sprite, transform.translate(position).rotate(angle));
	//window.draw(shape, transform);
}

void Asteroid::update(float deltaTime) {
	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += sf::Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

	if (position.x < size) {
		direction.x = abs(direction.x);
	}
	else if (position.x > FileMenager::screenData.size_width - size) {
		direction.x = -abs(direction.x);
	}

	if (position.y < size) {
		direction.y = abs(direction.y);
	}
	else if (position.y > FileMenager::screenData.size_height - size) {
		direction.y = -abs(direction.y);
	}

	for (const auto& entity : EntitiesList::entities) {
		if (entity->getEntityType() == EntityType::TYPE_ASTEROID && entity != this) {
			Asteroid* otherAsteroid = dynamic_cast<Asteroid*>(entity);
			if (otherAsteroid) {
				if (physics::intersects(this->position, size, otherAsteroid->position, otherAsteroid->size)) {
					direction = -direction;
					otherAsteroid->direction = -otherAsteroid->direction;
				}
			}
		}
	}
}

const float Asteroid::getRandomVelocity(const float& base)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.75 * base, 1.25 * base);

	return dist(gen);
}

const sf::Vector2f Asteroid::getRandomPosition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xAxis(size / 2, FileMenager::screenData.size_width - size / 2);
	std::uniform_real_distribution<float> yAxis(size / 2, FileMenager::screenData.size_height - size / 2);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}

const sf::CircleShape& Asteroid::getVertexShape() const
{
	return shape;
}

const EntityType Asteroid::getEntityType()
{
	return EntityType::TYPE_ASTEROID;
}

const sf::Vector2f Asteroid::getRandomDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0, 2.0f * M_PI);

	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}
