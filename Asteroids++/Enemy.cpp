#include "Enemy.h"
#include "Score.h"
#include "WindowBox.h"

Enemy::Enemy(float health, float speed, SpriteInfo spriteInfo) :
	Entity(getRandomPosition(), physics::getRandomAngle(), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_size), Color::Red, spriteInfo),
	health(health),
	healthBar(size, 3.0f, Color::Red, Color::Black, health, Vector2f(-100.0f, -100.0f)),
	direction(physics::getRandomDirection()),
	speed(speed),
	crit("CRIT", 0),
	critTimer(2.0f, false)
{
	crit.setColorText(Color::Red);
	crit.setTextPosition(position);
	crit.setSize(32);
}

void Enemy::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if (Game::hitboxesVisibility) window.draw(shape, transform);
	if (critTimer.isEffectActive()) window.draw(crit.getText());
	getHealthBar().draw(window);
}

void Enemy::update(float deltaTime)
{
	updateHealthBar();
	crit.setTextPosition(Vector2f(position.x - crit.getText().getLocalBounds().width / 2, position.y - crit.getText().getLocalBounds().height));

	if (critTimer.isEffectActive()) {
		critTimer.updateEffectDuration(deltaTime);

		float opacity = 255.0f * (critTimer.getEffectDuration() / 0.4f);

		Color color = crit.getText().getFillColor();
		color.a = static_cast<Uint8>(opacity);

		crit.setColorText(color);
	}
}

const EntityType Enemy::getEntityType()
{
	return EntityType::TYPE_ENEMY;
}

void Enemy::bounceCollisionDetection()
{
	Game::foreachEntity([&](Entity* entity) {
		if ((entity->getEntityType() == EntityType::TYPE_ENEMY && entity->spriteInfo.spriteType != Sprites::COMET)
			&& entity != this) {
			Enemy* otherEnemy = dynamic_cast<Enemy*>(entity);

			if (!otherEnemy) return;

			if (physics::intersects(this->position, radius, otherEnemy->position, otherEnemy->radius)) {
				const auto bounceDirection = physics::bounceDirection(this, otherEnemy, 0.01f);

				this->position += bounceDirection.second;
				otherEnemy->position -= bounceDirection.second;

				this->direction -= bounceDirection.first;
				otherEnemy->direction += bounceDirection.first;
			}
		}
	});
}

const Vector2f Enemy::getRandomPosition() const
{
	auto player = Game::doesEntityExist(EntityType::TYPE_PLAYER);

	if (!player) return Vector2f();

	Vector2f randomPosition;
	
	do {
		randomPosition = physics::getRandomPosition(size);
	} while (physics::intersects(randomPosition, radius, player->position, player->radius * 6.0f));
	
	return randomPosition;
}

const Bar& Enemy::getHealthBar() const
{
	return healthBar;
}

void Enemy::updateHealthBar()
{
	healthBar.updatePosition(Vector2f{ position.x - radius, position.y + radius });
	healthBar.updateValue(health);
}

const float Enemy::getHealth()
{
	return health;
}

void Enemy::updateHealth(const float& newValue)
{
	health -= newValue;
}