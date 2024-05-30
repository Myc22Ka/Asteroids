#include "Entity.h"
#include "FileMenager.h"
#include "DeathScreen.h"
#include "Physics.h"
#include "BlackHole.h"

const float spiralingSpeed = 15.0f;

Entity::Entity(Vector2f position, float angle, float size, Color hitboxColor, SpriteInfo spriteInfo)
	: position(position), angle(angle), size(size), hitboxColor(hitboxColor), radius(float(static_cast<int>(size) >> 1)), spriteInfo(spriteInfo) , spiraling(false), spiralingTarget(nullptr)
{
}

void Entity::update(float deltaTime)
{
	if (spiraling) {

		float distanceToBlackHole = physics::length(this->position - spiralingTarget->position);
		float targetDistance = spiralingTarget->radius / 2.0f;

		if (distanceToBlackHole > targetDistance) {
			// Calculate new position for spiraling effect
			float angle = deltaTime * spiralingSpeed / 3.0f; // spiralingSpeed should be defined
			float newX = cos(angle) * (this->position.x - spiralingTarget->position.x) - sin(angle) * (this->position.y - spiralingTarget->position.y) + spiralingTarget->position.x;
			float newY = sin(angle) * (this->position.x - spiralingTarget->position.x) + cos(angle) * (this->position.y - spiralingTarget->position.y) + spiralingTarget->position.y;

			// Move slightly towards the black hole
			Vector2f direction = physics::normalize(spiralingTarget->position - this->position) * spiralingSpeed;
			this->position = Vector2f(newX, newY) + direction * spiralingSpeed * deltaTime;
		}
		else {
			spiralingTarget->devour(this);
		}
	}
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
	if (spriteInfo.frames.size() == 0) return;

	spriteInfo.currentSpriteLifeTime -= deltaTime;

	if (spriteInfo.currentSpriteLifeTime <= 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (static_cast<unsigned long long>(spriteInfo.spriteState) + 1) % spriteInfo.frames.size();
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}

void Entity::setSpriteFullCycle(SpriteInfo& spriteInfo) {
	if (spriteInfo.frames.size() == 0) return;

	if (spriteInfo.currentSpriteLifeTime <= 0) {
		spriteInfo.currentSpriteLifeTime = spriteInfo.defaultSpriteLifeTime;
		spriteInfo.spriteState = (static_cast<unsigned long long>(spriteInfo.spriteState) + 1) % spriteInfo.frames.size();
		updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
	}
}

void Entity::startSpiraling(BlackHole* blackHole) {
	spiraling = true;
	spiralingTarget = blackHole;
}