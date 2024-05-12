#include "Strauner.h"
#include "WindowBox.h"
#include "EnemyBullet.h"
#include "Pickup.h"

Strauner::Strauner() : Enemy(2000.0f + 20.0f * floor(Score::getScore() / FileMenager::screenData.game_next_level_spike), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed), getSprite(Sprites::STRAUNER)),
changePosition(5.0f, false),
shoot(0.0f, false),
hue(0.0f)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void Strauner::render(RenderWindow& window)
{
	Enemy::render(window);
}

void Strauner::update(float deltaTime)
{
	Enemy::update(deltaTime);

	hue += fmod(deltaTime * 60.0f, 360.0f); // Adjust the multiplier as needed for the speed of color change

	// Convert HSL to RGB
	float c = 1.0f;
	float x = (1.0f - fabs(fmod(hue / 60.0f, 2) - 1.0f)) * c;
	float m = 0.0f;

	float r, g, b;
	if (hue >= 0 && hue < 60) {
		r = c;
		g = x;
		b = 0;
	}
	else if (hue >= 60 && hue < 120) {
		r = x;
		g = c;
		b = 0;
	}
	else if (hue >= 120 && hue < 180) {
		r = 0;
		g = c;
		b = x;
	}
	else if (hue >= 180 && hue < 240) {
		r = 0;
		g = x;
		b = c;
	}
	else if (hue >= 240 && hue < 300) {
		r = x;
		g = 0;
		b = c;
	}
	else {
		r = c;
		g = 0;
		b = x;
	}

	Color rainbowColor(static_cast<sf::Uint8>((r + m) * 255), static_cast<sf::Uint8>((g + m) * 255), static_cast<sf::Uint8>((b + m) * 255));

	Game::addParticle(new Particle(position, angle, spriteInfo.spriteType, rainbowColor, 0.5f));

    if (Game::freeze.isEffectActive()) return;

    changePosition.updateEffectDuration(deltaTime);
	shoot.updateEffectDuration(deltaTime);

	angle += FileMenager::enemiesData.asteroid_spin * deltaTime;

	Entity* player = Game::getEntities().back();
	Vector2f playerPosition = player->position;

	Vector2f directionToPlayer = physics::normalize(playerPosition - position);
	angle = atan2(directionToPlayer.y, directionToPlayer.x) * 180 / physics::getPI();


	if (getHealth() > 2000.0f / 2) {

	float angleOffset = rand() * physics::getPI() / 180.0f;
	float cosAngle = cos(angleOffset);
	float sinAngle = sin(angleOffset);
	Vector2f slightlyOffDirection = Vector2f(directionToPlayer.x * cosAngle - directionToPlayer.y * sinAngle,
		directionToPlayer.x * sinAngle + directionToPlayer.y * cosAngle);

	position += directionToPlayer * speed * deltaTime;

		if (!shoot.isEffectActive()) {
			shoot.startEffect(0.7f);

			Game::addEntity(new EnemyBullet(position, slightlyOffDirection, angle, Sprites::HOMING_BULLET));
			SoundData::play(Sounds::ALIEN_SHOOT1);
		}
	}
	else {
		if (!shoot.isEffectActive()) {

			shoot.startEffect(1.4f);

			for (size_t i = 0; i < 7; i++)
			{
				Game::addEntity(new EnemyBullet(position + physics::getRandomDirection() * 30.0f, directionToPlayer, angle, Sprites::HOMING_BULLET));
			}
			SoundData::play(Sounds::ALIEN_SHOOT1);
		}
	}

    setSpriteFullCycle(deltaTime);
}

void Strauner::collisionDetection() {}

void Strauner::destroy()
{
	Game::replaceEntity(this, new Explosion(position, size));

	Game::addEntity(new Pickup(position));

	Score::addScore(1000);
	SoundData::play(Sounds::EXPLOSION);
}
