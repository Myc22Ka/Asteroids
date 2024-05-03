#include "Asteroid.h"
#include "Score.h"
#include "WindowBox.h"

Asteroid::Asteroid(float health, float speed, SpriteInfo spriteInfo) :
	Entity(getRandomPosition(), physics::getRandomAngle(), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_size), Color::Red, spriteInfo),
	health(health),
	healthBar(size, 3.0f, Color::Red, Color::Black, health, Vector2f(-100.0f, -100.0f)),
	direction(physics::getRandomDirection()),
	speed(speed)
{
}

const EntityType Asteroid::getEntityType()
{
	return EntityType::TYPE_ENEMY;
}

void Asteroid::bounceCollisionDetection()
{
	Game::foreachEntity([&](Entity* entity) {
		if ((entity->getEntityType() == EntityType::TYPE_ENEMY && entity->spriteInfo.spriteType != Sprites::COMET)
			&& entity != this) {
			Asteroid* otherAsteroid = dynamic_cast<Asteroid*>(entity);

			if (!otherAsteroid) return;

			if (physics::intersects(this->position, radius, otherAsteroid->position, otherAsteroid->radius)) {
				const auto bounceDirection = physics::bounceDirection(this, otherAsteroid, 0.01f);

				this->position += bounceDirection.second;
				otherAsteroid->position -= bounceDirection.second;

				this->direction -= bounceDirection.first;
				otherAsteroid->direction += bounceDirection.first;
			}
		}
	});
}

const Vector2f Asteroid::getRandomPosition() const
{
	auto player = Game::doesEntityExist(EntityType::TYPE_PLAYER);

	if (!player) return Vector2f();

	Vector2f randomPosition;
	
	do {
		randomPosition = physics::getRandomPosition(size);
	} while (physics::intersects(randomPosition, radius, player->position, player->radius * 6.0f));
	
	return randomPosition;
}

const Bar& Asteroid::getHealthBar() const
{
	return healthBar;
}

void Asteroid::updateHealthBar()
{
	healthBar.updatePosition(Vector2f{ position.x - radius, position.y + radius });
	healthBar.updateValue(health);
}

const float Asteroid::getHealth()
{
	return health;
}

void Asteroid::updateHealth(const float& newValue)
{
	health -= newValue;
}