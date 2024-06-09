#include "MultiAsteroid.h"
#include "WindowBox.h"
#include "SingleAsteroid.h"
#include "Pickup.h"

MultiAsteroid::MultiAsteroid(): Enemy(20.0f + 20.0f * floor(Score::getScore() / FileMenager::screenData.game_next_level_spike), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed), getSprite(Sprites::MULTI_ASTEROID))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void MultiAsteroid::render(RenderWindow& window)
{
	Enemy::render(window);
}

void MultiAsteroid::update(float deltaTime)
{
	Enemy::update(deltaTime);

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

	//setSpriteFullCycle(deltaTime);

	collisionDetection();
}

void MultiAsteroid::collisionDetection()
{
	bounceCollisionDetection();
}

void MultiAsteroid::destroy()
{
	Game::replaceEntity(this, new Explosion(position, size));

	auto asteroid1 = new SingleAsteroid(position, physics::getRandomDirection());
	auto asteroid2 = new SingleAsteroid(Vector2f(position.x + asteroid1->radius, position.y + asteroid1->radius), physics::getRandomDirection());

	const auto bounceDirection = physics::bounceDirection(asteroid1, asteroid2, 1.0f);

	asteroid1->position += bounceDirection.second;
	asteroid2->position -= bounceDirection.second;

	asteroid1->direction -= bounceDirection.first;
	asteroid2->direction += bounceDirection.first;

	Game::addEntity(new SingleAsteroid(asteroid1->position, asteroid1->direction));
	Game::addEntity(new SingleAsteroid(asteroid2->position, asteroid2->direction));

	Game::addEntity(new Pickup(position, Sprites::PICKUP_EXTRA_BULLET));

	Score::addScore(40);
	SoundData::play(Sounds::EXPLOSION);
}
