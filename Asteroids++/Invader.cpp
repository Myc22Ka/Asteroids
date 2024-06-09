#include "Invader.h"
#include "WindowBox.h"
#include "EnemyBullet.h"
#include "Pickup.h"

Invader::Invader() : Enemy(500.0f + 60.0f * floor(Score::getScore() / FileMenager::screenData.game_next_level_spike), physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed) + 150.0f, getSprite(Sprites::INVADER)),
changePosition(5.0f, false),
shoot(0.0f, false)
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void Invader::render(RenderWindow& window)
{
    Enemy::render(window);
}

void Invader::update(float deltaTime)
{
    Enemy::update(deltaTime);

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

    float bulletAngle = atan2(slightlyOffDirection.y, slightlyOffDirection.x) * 180 / physics::getPI();

    if (physics::distance(newPosition, position) <= 100.0f) {
        if (!shoot.isEffectActive()) {
            shoot.startEffect(1.0f);

            Game::addEntity(new EnemyBullet(position, slightlyOffDirection, bulletAngle, Sprites::ENEMY_BULLET));
            SoundData::play(Sounds::ALIEN_SHOOT1);
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

    Score::addScore(200);
    SoundData::play(Sounds::EXPLOSION);
}