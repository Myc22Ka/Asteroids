#include "Asteroid.h"
#include "Score.h"
#include "WindowBox.h"

Asteroid::Asteroid(float health, SpriteInfo spriteInfo) :
	Entity(getRandomPosition(), physics::getRandomAngle(), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_size), Color::Red, spriteInfo),
	health(health),
	healthBar(size, 3.0f, Color::Red, Color::Black, health, Vector2f(-100.0f, -100.0f)),
	direction(physics::getRandomDirection()),
	speed(physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed))
{
}

void Asteroid::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if(Game::hitboxesVisibility) window.draw(shape, transform);
	healthBar.draw(window);
}

void Asteroid::update(float deltaTime) {
	healthBar.updatePosition(Vector2f{ position.x - radius, position.y + radius });
	healthBar.updateValue(health);

	if (Game::freeze.isEffectActive()) return;

	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
	position += Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

	if (position.x < radius) {
		direction.x = abs(direction.x);
	}
	else if (position.x > WindowBox::getVideoMode().width - radius) {
		direction.x = -abs(direction.x);
	}

	if (position.y < radius) {
		direction.y = abs(direction.y);
	}
	else if (position.y > WindowBox::getVideoMode().height - radius) {
		direction.y = -abs(direction.y);
	}

	setSpriteFullCycle(deltaTime);

	collisionDetection();
}

void Asteroid::collisionDetection()
{
	Game::foreachEntity([&](Entity* entity) {
		if ((entity->getEntityType() == EntityType::TYPE_ENEMY_MULTI_ASTEROID || entity->getEntityType() == EntityType::TYPE_ENEMY_SINGLE_ASTEROID)
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
