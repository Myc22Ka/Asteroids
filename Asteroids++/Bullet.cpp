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
    float minTimeToEnemy = 0.3f;

    Game::foreachEntity([&](Entity* entity) {
        if (Game::isEnemy(entity))
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
        if (Game::isEnemy(entity)) enemyHit(entity);
    }
}

void Bullet::enemyHit(Entity* entity) {
    Enemy* enemy = dynamic_cast<Enemy*>(entity);

    if (physics::intersects(position, radius, enemy->position, enemy->radius) && lifeTime > 0 && hitEnemies.find(enemy) == hitEnemies.end()) {
        if (!Player::playerStats.bulletType.piercing) lifeTime = 0;

        auto critHit = physics::rollDice(Player::playerStats.critChance);

        critHit ? enemy->updateHealth(Player::playerStats.bulletDamage * 2) : enemy->updateHealth(Player::playerStats.bulletDamage);

        if (enemy->getHealth() > 0) {
            hitEnemies.insert(enemy);
            if (critHit) {
                enemy->critTimer.startEffect(0.3f);
                SoundData::play(Sounds::CRITHIT);
            }

            Clock clock;
			thread t([enemy, clock, critHit]() {
				if(!critHit) SoundData::play(Sounds::HIT);
				enemy->spriteInfo.sprite.setColor(Color::Red);

				Color startColor = Color::Red;
				Color endColor = Color::White;

				while (clock.getElapsedTime().asSeconds() < 0.2f) {
					float progress = clock.getElapsedTime().asSeconds() / 0.2f;
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

            return;
        }

        enemy->destroy();
    }
}