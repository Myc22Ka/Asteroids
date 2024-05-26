#include "Entity.h"
#include "FileMenager.h"
#include "DeathScreen.h"

Entity::Entity(Vector2f position, float angle, float size, Color hitboxColor, SpriteInfo spriteInfo)
	: position(position), angle(angle), size(size), hitboxColor(hitboxColor), radius(float(static_cast<int>(size) >> 1)), spriteInfo(spriteInfo) 
{
}

bool Entity::isActive() const
{
	return active;
}

void Entity::setActive(const bool& active)
{
	this->active = active;
}

const Sprites Entity::getSpriteType() const {
	return this->spriteInfo.spriteType;
}

void Entity::drawHitboxes()
{
	shape.setRadius(radius);
	Vector2f center(radius, radius);

	shape.setOrigin(center);

	shape.setFillColor(Color::Transparent);
	shape.setOutlineColor(hitboxColor);
	shape.setOutlineThickness(1.5f);
}

void Entity::drawHitboxes(const float& radius)
{
	shape.setRadius(radius);
	Vector2f center(radius, radius);

	shape.setOrigin(center);

	shape.setFillColor(Color::Transparent);
	shape.setOutlineColor(hitboxColor);
	shape.setOutlineThickness(1.5f);
}

void Entity::setSpriteFullCycle(const double& deltaTime){
	spriteInfo.currentSpriteLifeTime -= deltaTime;

	if (spriteInfo.currentSpriteLifeTime <= 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}

void Entity::setSpriteFullCycle(SpriteInfo& spriteInfo) {

	if (spriteInfo.currentSpriteLifeTime <= 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}