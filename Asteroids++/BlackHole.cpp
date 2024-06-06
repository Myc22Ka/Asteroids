#include "BlackHole.h"
#include "Pickup.h"

BlackHole::BlackHole() : Enemy(Player::playerStats.bulletDamage * 10.0f, 0.0f, getSprite(Sprites::BLACKHOLE))
{
	size *= 4;
	radius *= 4;

	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void BlackHole::render(RenderWindow& window)
{
	Enemy::render(window);
}

void BlackHole::update(float deltaTime)
{
	Enemy::update(deltaTime);

	setSpriteFullCycle(deltaTime);

	collisionDetection();
}

void BlackHole::collisionDetection()
{
	Game::foreachEntity([&](Entity* entity) {
		if (entity != this && !Game::isEntityInsideGruop(entity, Enemy::blackHoleGroup)) {

			if (physics::intersects(this->position, radius, entity->position, entity->radius)) {
				entity->startSpiraling(this);
			}
		}
	});
}

void BlackHole::devour(Entity* entity) {
	size += entity->size * 0.15f;
	increaseHealth(Player::playerStats.bulletDamage * 3.0f);

	radius = size / 2.0f;
	entity->spiraling = false;

	this->scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
	this->drawHitboxes();

	Clock clock;
	thread t([this, clock]() {
		spriteInfo.sprite.setColor(Color::Green);

		Color startColor = Color::Green;
		Color endColor = Color::White;

		while (clock.getElapsedTime().asSeconds() < 0.2f) {
			float progress = clock.getElapsedTime().asSeconds() / 0.2f;
			Color interpolatedColor = Color(
				static_cast<Uint8>(startColor.r + progress * (endColor.r - startColor.r)),
				static_cast<Uint8>(startColor.g + progress * (endColor.g - startColor.g)),
				static_cast<Uint8>(startColor.b + progress * (endColor.b - startColor.b)),
				static_cast<Uint8>(startColor.a + progress * (endColor.a - startColor.a)));
			spriteInfo.sprite.setColor(interpolatedColor);

			this_thread::sleep_for(chrono::milliseconds(35));
		}
		spriteInfo.sprite.setColor(Color::White);
	});

	t.detach();

	Game::replaceEntity(entity, new Explosion(entity->position, entity->size));
}

void BlackHole::destroy()
{
	Game::replaceEntity(this, new Explosion(position, radius));

	Score::addScore(1000);
	SoundData::play(Sounds::EXPLOSION);
}