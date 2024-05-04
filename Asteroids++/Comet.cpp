#include "Comet.h"
#include "WindowBox.h"
#include "Pickup.h"

Comet::Comet() : Asteroid(500, physics::getRandomFloatValue(FileMenager::enemiesData.asteroid_speed) + 100.0f, getSprite(Sprites::COMET))
{
	scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, size);

	drawHitboxes();
}

void Comet::render(RenderWindow& window)
{
    Transform transform;
    window.draw(spriteInfo.sprite, transform.translate(position).rotate(angle));
    if (Game::hitboxesVisibility) window.draw(shape, transform);
    getHealthBar().draw(window);
}

void Comet::update(float deltaTime)
{
    updateHealthBar();

    Game::addParticle(new Particle(position, angle, spriteInfo.spriteType, Color(255,255,255,50), 0.5f));

    if (Game::freeze.isEffectActive()) return;

    angle += FileMenager::enemiesData.asteroid_spin * deltaTime;
    position += Vector2f(direction.x * speed * deltaTime, direction.y * speed * deltaTime);

    if (position.x < -radius) {
        position.x = WindowBox::getVideoMode().width + radius;
    }
    else if (position.x > WindowBox::getVideoMode().width + radius) {
        position.x = -radius;
    }

    if (position.y < -radius) {
        position.y = WindowBox::getVideoMode().height + radius;
    }
    else if (position.y > WindowBox::getVideoMode().height + radius) {
        position.y = -radius;
    }

    setSpriteFullCycle(deltaTime);
}

void Comet::collisionDetection() {}

void Comet::destroy()
{
    Game::replaceEntity(this, new Explosion(position, size));

    Game::addEntity(new Pickup(position, Pickup::getRandomFromGroup(Pickup::bulletTypes)));

    Score::addScore(10);
    SoundData::play(Sounds::EXPLOSION);
}