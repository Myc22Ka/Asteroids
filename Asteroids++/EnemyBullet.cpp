#include "EnemyBullet.h"
#include "DeathScreen.h"

EnemyBullet::EnemyBullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType) : Bullet(position, direction, angle, spriteType)
{
    setRotation(spriteInfo.sprite, angle);
    drawHitboxes();

    scaleSprite(spriteInfo.sprite, int(FileMenager::playerData.bullet_size), int(FileMenager::playerData.bullet_size));
}

void EnemyBullet::update(float deltaTime)
{
    lifeTime -= deltaTime;

    position += Vector2f(direction.x * Player::playerStats.bulletSpeed * deltaTime, direction.y * Player::playerStats.bulletSpeed * deltaTime);
    if (lifeTime <= 0) {
        Game::removeEntity(this);
        return;
    }

    if (Game::getEntities().back()->getEntityType() == TYPE_PLAYER) {
        auto player = dynamic_cast<Player*>(Game::getEntities().back());

        if (physics::intersects(position, radius, player->position, player->radius) && lifeTime > 0 && !Player::playerStats.shield.isEffectActive() && DeathScreen::isScreenOver()) {
            lifeTime = 0;
            player->destroy();
        }
    }
}
const EntityType EnemyBullet::getEntityType()
{
    return EntityType::TYPE_ENEMY_BULLET;
}