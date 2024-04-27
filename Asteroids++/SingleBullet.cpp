#include "SingleBullet.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"

SingleBullet::SingleBullet(Vector2f position, Vector2f direction, float& angle) : Bullet(position, direction, angle)
{
    setRotation(spriteInfo.sprite, angle);
    drawHitboxes();

    scaleSprite(spriteInfo.sprite, FileMenager::playerData.bullet_size, size);
}

const EntityType SingleBullet::getEntityType()
{
	return EntityType::TYPE_BULLET_SINGLE;
}