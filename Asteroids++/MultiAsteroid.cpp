#include "MultiAsteroid.h"

MultiAsteroid::MultiAsteroid(): Asteroid(20, getSprite(Sprites::MULTI_ASTEROID))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

const EntityType MultiAsteroid::getEntityType()
{
	return EntityType::TYPE_ENEMY_MULTI_ASTEROID;
}
