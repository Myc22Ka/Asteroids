#include "Asteroid.h"

#include "Bullet.h"
#include "EntitiesList.h"
#include <iostream>

constexpr double M_PI = 3.14159265358979323846;

Asteroid::Asteroid() :
	Entity(sf::Vector2f(600, 300), 0),
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
	
}
