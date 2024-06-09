#include "Bullet.h"
#include "SingleAsteroid.h"
#include "MultiAsteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"
#include "Pickup.h"
#include "Particle.h"

Bullet::Bullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType, Color color) :
    direction(direction),
    Entity(position, angle, Player::playerStats.bulletSize, color, getSprite(spriteType)),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
}

Bullet::Bullet(Vector2f position, Vector2f direction, float& angle, Sprites spriteType, Color color, float size) :
    direction(direction),
    Entity(position, angle, size, color, getSprite(spriteType)),
    lifeTime(FileMenager::playerData.bullet_lifetime)
{
}

void Bullet::homeToEnemy(float deltaTime) {
    const auto enemy = findNearestEnemy();

    if (!enemy) return;

    Vector2f directionToEnemy = enemy->position - position;
    float distanceToEnemy = physics::distance(position, enemy->position);
    float timeToEnemy = distanceToEnemy / Player::playerStats.bulletSpeed;

    Vector2f normalizedDirection = physics::normalize(directionToEnemy);
    float speed = Player::playerStats.bulletSpeed;
    Vector2f movement = Vector2f(normalizedDirection.x * speed * deltaTime, normalizedDirection.y * speed * deltaTime);

    position += movement;

    Vector2f homingDirection = physics::calculateDirection(position, enemy->position);

    if (position.x < enemy->position.x) {
        position += homingDirection * speed * deltaTime;
    }
    else if (position.x > enemy->position.x) {
        position += homingDirection * speed * deltaTime;
    }
}

Entity* Bullet::findNearestEnemy() const
{
    Entity* nearestEnemy = nullptr;
    float minTimeToEnemy = FileMenager::timingsData.default_bullet_homing_time;

    Game::foreachEntity([&](Entity* entity) {
        if (entity->getEntityType() == EntityType::TYPE_ENEMY)
        {
            float timeToEnemy = physics::distance(position, entity->position) / Player::playerStats.bulletSpeed;

            if (timeToEnemy >= minTimeToEnemy) return nullptr;

            minTimeToEnemy = timeToEnemy;
            nearestEnemy = entity;
        }

        return nullptr;
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
        if (entity->getEntityType() == EntityType::TYPE_ENEMY) enemyHit(entity);
    }
}

void Bullet::enemyHit(Entity* entity) {
    Enemy* enemy = dynamic_cast<Enemy*>(entity);

    if (physics::intersects(position, radius, enemy->position, enemy->radius) && lifeTime > 0 && hitEnemies.find(enemy) == hitEnemies.end()) {
        if (Player::playerStats.bulletType != PIERCING) lifeTime = 0;

        auto critHit = physics::rollDice(Player::playerStats.critChance);

        critHit ? enemy->updateHealth(Player::playerStats.bulletDamage * 2) : enemy->updateHealth(Player::playerStats.bulletDamage);

        hitEnemies.insert(enemy);
        if (critHit) {
            enemy->critTimer.startEffect(FileMenager::timingsData.default_crit_timer);
            SoundData::play(Sounds::CRITHIT);
        }

        damageEnemy(enemy, critHit, Color::Red);

        if (Player::playerStats.bulletType == POISON) {
            thread t([enemy]() {
                for (int i = 0; i < FileMenager::playerData.player_bullet_poison_amount; i++) {
                    if (enemy->getHealth() < 0) break;

                    enemy->updateHealth(enemy->getMaxHealth() * FileMenager::playerData.player_bullet_poison_damage);
                    Bullet::damageEnemy(enemy, true, Color::Magenta);

                    this_thread::sleep_for(chrono::milliseconds(FileMenager::timingsData.default_poison_dose_time));
                }
            });

            t.detach();
        }
    }
}

void Bullet::damageEnemy(Enemy* enemy, bool critHit, Color color){
    Clock clock;
    thread t([enemy, clock, critHit, color]() {
        if (!critHit) SoundData::play(Sounds::HIT);
        enemy->spriteInfo.sprite.setColor(color);

        Color startColor = color;
        Color endColor = Color::White;

        while (clock.getElapsedTime().asSeconds() < FileMenager::timingsData.default_hit_effect_time) {
            float progress = clock.getElapsedTime().asSeconds() / FileMenager::timingsData.default_hit_effect_time;
            Color interpolatedColor = Color(
                static_cast<Uint8>(startColor.r + progress * (endColor.r - startColor.r)),
                static_cast<Uint8>(startColor.g + progress * (endColor.g - startColor.g)),
                static_cast<Uint8>(startColor.b + progress * (endColor.b - startColor.b)),
                static_cast<Uint8>(startColor.a + progress * (endColor.a - startColor.a)));
            enemy->spriteInfo.sprite.setColor(interpolatedColor);

            this_thread::sleep_for(chrono::milliseconds(35));
        }
        enemy->spriteInfo.sprite.setColor(Color::White);
        });

    t.detach();
}