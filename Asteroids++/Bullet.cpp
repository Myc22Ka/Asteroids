#include "Bullet.h"
#include "SingleAsteroid.h"
#include "MultiAsteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"
#include "Pickup.h"
#include "Particle.h"

constexpr double M_PI = 3.14159265358979323846;

Bullet::Bullet(Vector2f position, Vector2f direction, float& angle) :
    direction(direction), 
    Entity(position, angle, Player::playerStats.bulletSize, Color::Green, getSprite(Player::getPlayerBulletSprite())),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
}

void Bullet::update(float deltaTime)
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

void Bullet::homeToEnemy(float deltaTime) {
    const auto enemy = findNearestEnemy();

    if (!enemy) return;

    Vector2f directionToEnemy = enemy->position - position;
    float distanceToEnemy = physics::distance(position, enemy->position);
    float timeToEnemy = distanceToEnemy / Player::playerStats.bulletSpeed;

    float targetAngle = atan2(directionToEnemy.y, directionToEnemy.x) * 180.0f / M_PI;

    float adjustedAngle = targetAngle - angle;

    angle = targetAngle;

    spriteInfo.rotation = targetAngle;

    setRotation(spriteInfo.sprite, adjustedAngle);

    Vector2f normalizedDirection = physics::normalize(directionToEnemy);
    int speed = Player::playerStats.bulletSpeed;
    Vector2f movement = Vector2f(normalizedDirection.x * speed * deltaTime, normalizedDirection.y * speed * deltaTime);

    position += movement;

    Vector2f homingDirection = physics::calculateDirection(position, enemy->position);

    if (position.x < enemy->position.x) {
        position += homingDirection * float(speed) * deltaTime;
    }
    else if (position.x > enemy->position.x) {
        position += homingDirection * float(speed) * deltaTime;
    }
}

Entity* Bullet::findNearestEnemy() const
{
    Entity* nearestEnemy = nullptr;
    double minTimeToEnemy = 1.3;

    Game::foreachEntity([&](Entity* entity) {
        if (Game::isEnemy(entity))
        {
            float timeToEnemy = physics::distance(position, entity->position) / Player::playerStats.bulletSpeed;

            if (timeToEnemy >= minTimeToEnemy) return nullptr;

            minTimeToEnemy = timeToEnemy;
            nearestEnemy = entity;
        }
    });

    return nearestEnemy;
}

void Bullet::render(RenderWindow& window)
{
    Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
    if (Game::hitboxesVisibility) window.draw(shape, transform);
}

void Bullet::collisionDetection()
{
    for (auto& entity : Game::getEntities())
    {
        if (Game::isEnemy(entity)) asteroidHit(entity);
    }
}

void Bullet::asteroidHit(Entity* entity) {
    Asteroid* asteroid = dynamic_cast<Asteroid*>(entity);

    if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0 && hitAsteroids.find(asteroid) == hitAsteroids.end()) {
        if (!Player::playerStats.bulletType.piercing) lifeTime = 0;
        asteroid->health -= Player::playerStats.bulletDamage;

        if (asteroid->health > 0) {
            hitAsteroids.insert(asteroid);
            return;
        }

        if (asteroid->getEntityType() == EntityType::TYPE_ENEMY_SINGLE_ASTEROID) destroySingleAsteroid(entity);
        if (asteroid->getEntityType() == EntityType::TYPE_ENEMY_MULTI_ASTEROID) destroyMultiAsteroid(entity);
    }
}

void Bullet::spawnPickup(const Vector2f& position)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    auto propability = dist(gen);

    if (propability > 0.5) return;

    if (propability < 0.01) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::HEART1UP)));
        return;
    }
    if (propability < 0.05) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_FREEZE)));
        return;
    }
    if (propability < 0.1) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_PIERCING)));
        return;
    }
    if (propability < 0.2) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_4)));
        return;
    }
    if (propability < 0.3) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_3)));
        return;
    }
    if (propability < 0.4) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_2)));
        return;
    }
    if (propability < 0.5) {
        Game::addEntity(new Pickup(position, getSprite(Sprites::PICKUP_1)));
        return;
    }
    
}

void Bullet::destroySingleAsteroid(Entity* entity)
{
    SingleAsteroid* asteroid = dynamic_cast<SingleAsteroid*>(entity);

    Game::replaceEntity(asteroid, new Explosion(asteroid->position, asteroid->size));

    spawnPickup(asteroid->position);

    Score::score += 10;
    SoundData::play(Sounds::EXPLOSION);
}

void Bullet::destroyMultiAsteroid(Entity* entity)
{
    MultiAsteroid* asteroid = dynamic_cast<MultiAsteroid*>(entity);

    Game::replaceEntity(asteroid, new Explosion(asteroid->position, asteroid->size));

    auto asteroid1 = new SingleAsteroid(asteroid->position, physics::getRandomDirection());
    auto asteroid2 = new SingleAsteroid(Vector2f(asteroid->position.x + asteroid1->radius, asteroid->position.y + asteroid1->radius), physics::getRandomDirection());

    const auto bounceDirection = physics::bounceDirection(asteroid1, asteroid2, 1.0f);

    asteroid1->position += bounceDirection.second;
    asteroid2->position -= bounceDirection.second;

    asteroid1->direction -= bounceDirection.first;
    asteroid2->direction += bounceDirection.first;

    Game::addEntity(new SingleAsteroid(asteroid1->position, asteroid1->direction));
    Game::addEntity(new SingleAsteroid(asteroid2->position, asteroid2->direction));

    Score::score += 20;
    SoundData::play(Sounds::EXPLOSION);
}
