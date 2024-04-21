#include "SingleAsteroid.h"

SingleAsteroid::SingleAsteroid(): Asteroid(100, getSprite(Sprites::SINGLE_ASTEROID))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

SingleAsteroid::SingleAsteroid(Vector2f p, Vector2f d): Asteroid(100, getSprite(Sprites::SINGLE_ASTEROID))
{
	position = p;
	direction = d;
	size >>= 1;

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes(size >> 1);
}

const EntityType SingleAsteroid::getEntityType()
{
	return EntityType::TYPE_ENEMY_SINGLE_ASTEROID;
}
