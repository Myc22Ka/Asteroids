#include "Asteroid.h"

#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>
#include <random>

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid() :
		Entity(sf::Vector2f(600, 300), 0),
		direction(Asteroid::getRandomDirection()),
		position(Asteroid::getRandomPosition()),
		speed(Asteroid::getRandomVelocity(FileMenager::enemiesData.asteroid_speed)),
		shape(sf::LinesStrip, 9)
{
	auto size = FileMenager::playerData.size;

	shape[0].position = sf::Vector2f(0, 0);
	shape[1].position = sf::Vector2f(20, -20);
	shape[2].position = sf::Vector2f(40, -20);
	shape[3].position = sf::Vector2f(60, 0);
	shape[4].position = sf::Vector2f(60, 20);
	shape[5].position = sf::Vector2f(40, 40);
	shape[6].position = sf::Vector2f(20, 40);
	shape[7].position = sf::Vector2f(0, 20);
	shape[8].position = shape[0].position;

	// Calculate the center of the shape
	sf::Vector2f center(0.f, 0.f);
	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		center += shape[i].position;
	}
	center /= static_cast<float>(shape.getVertexCount());

	// Set the origin of the shape to its center
	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		shape[i].position -= center;
	}

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		shape[i].color = sf::Color::White;
	}
}

void Asteroid::render(sf::RenderWindow& window)
{
	sf::Transform transform;
	window.draw(shape, transform.translate(position).rotate(angle));
}

void Asteroid::update(float deltaTime) {
	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += sf::Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

	if (position.x < getEntitySize().width / 2) {
		direction.x = abs(direction.x);
	}
	else if (position.x > FileMenager::screenData.size_width - getEntitySize().width / 2) {
		direction.x = -abs(direction.x);
	}

	if (position.y < getEntitySize().height / 2) {
		direction.y = abs(direction.y);
	}
	else if (position.y > FileMenager::screenData.size_height - getEntitySize().height / 2) {
		direction.y = -abs(direction.y);
	}
}

const Size Asteroid::getEntitySize()
{
	return Size(60, 40);
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
	std::uniform_real_distribution<float> xAxis(getEntitySize().width / 2, FileMenager::screenData.size_width - getEntitySize().width / 2);
	std::uniform_real_distribution<float> yAxis(getEntitySize().height / 2, FileMenager::screenData.size_height - getEntitySize().height / 2);

	return sf::Vector2f(xAxis(gen), yAxis(gen));
}

const sf::VertexArray& Asteroid::getVertexShape() const
{
	return shape;
}

const sf::Vector2f Asteroid::getRandomDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0, 2.0f * M_PI);

	float angle = dist(gen);
	return sf::Vector2f(cos(angle), sin(angle));
}
