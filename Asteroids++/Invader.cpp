#include "Invader.h"
#include "WindowBox.h"
#include "EnemyBullet.h"
#include "Pickup.h"

Invader::Invader() : Enemy(300, physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed) + 150.0f, getSprite(Sprites::INVADER)),
changePosition(5.0f, false),
shoot(0.0f, false)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void Invader::render(RenderWindow& window)
{
	Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
	if (Game::hitboxesVisibility) window.draw(shape, transform);
	getHealthBar().draw(window);
}

void Invader::update(float deltaTime)
{
    updateHealthBar();

    if (Game::freeze.isEffectActive()) return;

    changePosition.updateEffectDuration(deltaTime);
    shoot.updateEffectDuration(deltaTime);

    Entity* player = Game::getEntities().back();
    Vector2f playerPosition = player->position;

    Vector2f directionToPlayer = physics::normalize(playerPosition - position);
    angle = atan2(directionToPlayer.y, directionToPlayer.x) * 180 / physics::getPI();

    float angleOffset = (rand() % 40 - 10) * physics::getPI() / 180.0f;
    float cosAngle = cos(angleOffset);
    float sinAngle = sin(angleOffset);
    Vector2f slightlyOffDirection = Vector2f(directionToPlayer.x * cosAngle - directionToPlayer.y * sinAngle,
        directionToPlayer.x * sinAngle + directionToPlayer.y * cosAngle);

    if (!changePosition.isEffectActive()) {
        newPosition = physics::getRandomPosition(radius);
        target = newPosition - position;
        changePosition.startEffect(5.0f);
    }

    if (physics::distance(newPosition, position) <= 100.0f) {
        if (!shoot.isEffectActive()) {
            shoot.startEffect(1.0f);

            Game::addEntity(new EnemyBullet(position, slightlyOffDirection, angle, Sprites::HOMING_BULLET));
            SoundData::play(Sounds::LASER_SHOOT);
        }
        return;
    }
    position += physics::normalize(target) * deltaTime * speed;

    setSpriteFullCycle(deltaTime);
}

void Invader::collisionDetection() {}

void Invader::destroy()
{
    Game::replaceEntity(this, new Explosion(position, size));

    for (size_t i = 0; i < 3; i++)
    {
        Game::addEntity(new Pickup(position + physics::getRandomDirection() * 15.0f, Pickup::getRandomFromGroup(Pickup::modifiers)));
    }

    Score::addScore(10);
    SoundData::play(Sounds::EXPLOSION);
}