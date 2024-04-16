#include "Entity.h"
#include "EntitiesList.h"
#include "FileMenager.h"

Entity::Entity(sf::Vector2f position, float angle, int spriteState, int size, sf::Color hitboxColor)
	: position(position), angle(angle), size(size), hitboxColor(hitboxColor) {}

void Entity::drawHitboxes()
{
	const auto newSize = size >> 1;

	shape.setRadius(newSize);
	sf::Vector2f center(newSize, newSize);

	shape.setOrigin(center);

	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(hitboxColor);
	shape.setOutlineThickness(1.5f);
}