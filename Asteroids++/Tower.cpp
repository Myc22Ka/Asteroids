#include "Tower.h"
#include "WindowBox.h"
#include "EnemyBullet.h"
#include "Pickup.h"

const float shootTime = 0.5f;
const int counter = 5;

Tower::Tower() : Enemy(10000.0f + 200.0f * floor(Score::getScore() / FileMenager::screenData.game_next_level_spike), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed), getSprite(Sprites::TOWER)),
shoot(shootTime, false),
changePosition(0.0f, false),
shootCounter(counter)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.hitboxSize, spriteInfo.spriteSize);

	drawHitboxes();

	angle = 0;
}

void Tower::render(RenderWindow& window)
{
	Enemy::render(window);
}

void Tower::update(float deltaTime)
{
	Enemy::update(deltaTime);

	if (Game::freeze.isEffectActive()) return;

	shoot.updateEffectDuration(deltaTime);
	changePosition.updateEffectDuration(deltaTime);
	float radius = 0.3f;
	float circularX = cos(changePosition.getEffectDuration()) * radius;
	float circularY = sin(changePosition.getEffectDuration()) * radius;

	Vector2f originalPosition = position;
	position.x = originalPosition.x + circularX;
	position.y = originalPosition.y + circularY;

	if (shootCounter == counter) {
		angle += 45;
		shootCounter = 0;
	}

	if (!shoot.isEffectActive()) {
		shoot.startEffect(shootTime);
		shootCounter++;

		for (int i = 0; i < 4; ++i) {
			float angle = i * 90.0f + this->angle;
			float radianAngle = angle * (physics::getPI() / 180.0f);
			float directionX = cos(radianAngle);
			float directionY = sin(radianAngle);

			float bulletAngle = atan2(directionY, directionX) * 180 / physics::getPI();

			Game::addEntity(new EnemyBullet(position, { directionX, directionY }, bulletAngle, Sprites::ENEMY_BULLET));
		}

		SoundData::play(Sounds::ALIEN_SHOOT1);
	}

	setSpriteFullCycle(deltaTime);
}

void Tower::collisionDetection() {}

void Tower::destroy()
{
	Game::replaceEntity(this, new Explosion(position, size));

	Game::addEntity(new Pickup(position));

	Score::addScore(1000);
	SoundData::play(Sounds::EXPLOSION);
}
