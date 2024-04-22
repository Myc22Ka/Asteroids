#include "SingleBullet.h"
#include "MultiAsteroid.h"
#include "SingleAsteroid.h"

SingleBullet::SingleBullet(Vector2f position, Vector2f direction, const float& angle) : Bullet(position, direction , angle)
{
    setRotation(spriteInfo.sprite, angle);
    drawHitboxes();

    scaleSprite(spriteInfo.sprite, FileMenager::playerData.bullet_size, size);
}

const EntityType SingleBullet::getEntityType()
{
	return EntityType::TYPE_BULLET_SINGLE;
}

void SingleBullet::singleAsteroidHit(const int& i)
{
    SingleAsteroid* asteroid = dynamic_cast<SingleAsteroid*>(Game::entities[i]);

    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0 && hitAsteroids.find(i) == hitAsteroids.end()) {
        if(!Player::playerStats.piercing) lifeTime = 0;
        asteroid->health -= Player::playerStats.bulletDamage;

        if (asteroid->health <= 0) destroySingleAsteroid(i);

        hitAsteroids.insert(i);
    }
}

void SingleBullet::multiAsteroidHit(const int& i)
{
    MultiAsteroid* asteroid = dynamic_cast<MultiAsteroid*>(Game::entities[i]);

    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0 && hitAsteroids.find(i) == hitAsteroids.end()) {
        if (!Player::playerStats.piercing) lifeTime = 0;
        asteroid->health -= Player::playerStats.bulletDamage;

        if (asteroid->health <= 0) destroyMultiAsteroid(i);

        hitAsteroids.insert(i);
    }
}
