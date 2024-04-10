#include "Entity.h"
#include "EntitiesList.h"

Entity::Entity(sf::Vector2f position, float angle) : position(position), angle(angle) {}

void Entity::playSound(Names name)
{
	Sound sound;
	sound.setFileName(name);
	sound.loadAndPlay();
}
