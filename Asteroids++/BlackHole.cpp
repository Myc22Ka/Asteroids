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

	if (Game::getGameState() == FREZZE) return;
		 
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
	size += entity->size * FileMenager::enemiesData.enemy_blackhole_increse_size;
	increaseHealth(Player::playerStats.bulletDamage * 3.0f);

	radius = size / 2.0f;
	entity->spiraling = false;

	this->scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);
	this->drawHitboxes();

	Bullet::damageEnemy(this, true, Color::Green);

	Game::replaceEntity(entity, new Explosion(entity->position, entity->size));
}

void BlackHole::destroy()
{
	Game::replaceEntity(this, new Explosion(position, radius));

	Score::addScore(500);
	SoundData::play(Sounds::EXPLOSION);
}