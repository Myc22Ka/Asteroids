#include "Explosion.h"

const Sprites EXPLOSIONS[] = { Sprites::EXPLOSION_1, Sprites::EXPLOSION_2, Sprites::EXPLOSION_3, Sprites::EXPLOSION_4 };

Explosion::Explosion(sf::Vector2f position, int asteroidSize) : Entity(position, 0, 256, sf::Color::Cyan, getSprite(setRandomSprite())) {
    //drawHitboxes();

    const auto newSize = size * asteroidSize / spriteInfo.hitboxSize;

    scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, newSize * 3 / 2);
}
Explosion::Explosion(Vector2f position, int s, SpriteInfo spriteInfo) : Entity(position, 0, 256, sf::Color::Cyan, getSprite(Sprites::COLLECTED))
{
    const auto newSize = size * s / spriteInfo.hitboxSize;

    scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, newSize * 3 / 2);
}

void Explosion::update(double deltaTime)
{
    if (spriteInfo.spriteState == spriteInfo.frames.size() - 1) Game::removeEntity(this);

    setSpriteFullCycle(deltaTime);
}

void Explosion::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    window.draw(spriteInfo.sprite, transform.translate(position));
    if (Game::hitboxesVisibility) window.draw(shape, transform);
}

const EntityType Explosion::getEntityType()
{
    return EntityType::TYPE_EXPLOSION;
}

void Explosion::collisionDetection() {}

Sprites Explosion::setRandomSprite()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(0, sizeof(EXPLOSIONS) / sizeof(EXPLOSIONS[0]) - 1);

    int randomIndex = dist(gen);

    return EXPLOSIONS[randomIndex];
}
