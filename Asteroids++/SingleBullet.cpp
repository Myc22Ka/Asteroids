#include "SingleBullet.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"

SingleBullet::SingleBullet(Vector2f position, Vector2f direction, float& angle) : Bullet(position, direction, angle, Player::getPlayerBulletSprite())
{
    setRotation(spriteInfo.sprite, angle);
    drawHitboxes();

    scaleSprite(spriteInfo.sprite, int(FileMenager::playerData.bullet_size), size);
}

void SingleBullet::update(float deltaTime)
{
    lifeTime -= deltaTime;

    position += Vector2f(direction.x * Player::playerStats.bulletSpeed * deltaTime, direction.y * Player::playerStats.bulletSpeed * deltaTime);
    if (lifeTime <= 0) {
        Game::removeEntity(this);
        return;
    }

    if (Player::playerStats.bulletType.homing && lifeTime < 0.9 * FileMenager::playerData.bullet_lifetime) homeToEnemy(deltaTime);

    collisionDetection();
}

const EntityType SingleBullet::getEntityType()
{
    return EntityType::TYPE_BULLET_SINGLE;
}