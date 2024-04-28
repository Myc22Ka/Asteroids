#include "Particle.h"

Particle::Particle(Vector2f position, float angle, Sprites sprites, Color color, double lifeTime, bool oneCycleLife) : Entity(position, angle, 64, Color::Yellow, getSprite(sprites)),
lifeTime(lifeTime), oneCycleLife(oneCycleLife)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
}

Particle::Particle(Vector2f position, float angle, Sprites sprites, Color color, double lifeTime) : Entity(position, angle, 64, Color::Yellow, getSprite(sprites)),
lifeTime(lifeTime)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	spriteInfo.sprite.setColor(color);
}

void Particle::render(RenderWindow& window)
{
	window.draw(spriteInfo.sprite, Transform().translate(position).rotate(angle));
}

void Particle::update(float deltaTime)
{
	lifeTime -= deltaTime;
	if (lifeTime <= 0 && !oneCycleLife) {
		Game::removeParticle(this);
		return;
	}
	if (oneCycleLife) {
		if (spriteInfo.spriteState == spriteInfo.frames.size() - 1) {
			Game::removeParticle(this);
			return;
		}

		setSpriteFullCycle(deltaTime);
	}
}

const EntityType Particle::getEntityType()
{
	return EntityType::TYPE_PARTICLE;
}

void Particle::collisionDetection() {}
