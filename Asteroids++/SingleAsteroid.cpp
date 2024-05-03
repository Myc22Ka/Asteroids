#include "SingleAsteroid.h"
#include "WindowBox.h"
#include "Game.h"
#include "Pickup.h"

SingleAsteroid::SingleAsteroid(): Asteroid(100.0f, physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed) + 50.0f, getSprite(Sprites::SINGLE_ASTEROID))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
	drawHitboxes();
}

SingleAsteroid::SingleAsteroid(Vector2f p, Vector2f d): Asteroid(100.0f, physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed) + 50.0f, getSprite(Sprites::SINGLE_ASTEROID))
{
	position = p;
	direction = d;
	size = radius;

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes(radius / 2);
}

void SingleAsteroid::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if (Game::hitboxesVisibility) window.draw(shape, transform);
	getHealthBar().draw(window);
}

void SingleAsteroid::update(float deltaTime)
{
	updateHealthBar();

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

void SingleAsteroid::collisionDetection()
{
	bounceCollisionDetection();
}

void SingleAsteroid::destroy()
{
	Game::replaceEntity(this, new Explosion(position, size));

	Game::addEntity(new Pickup(position));

	Score::addScore(10);
	SoundData::play(Sounds::EXPLOSION);
}
