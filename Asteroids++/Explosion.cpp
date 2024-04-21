#include "Explosion.h"

const Sprites EXPLOSIONS[] = { Sprites::EXPLOSION_1, Sprites::EXPLOSION_2, Sprites::EXPLOSION_3, Sprites::EXPLOSION_4 };

Explosion::Explosion(sf::Vector2f position, int asteroidSize) : Entity(position, 0, 256, sf::Color::Cyan, getSprite(setRandomSprite())) {
    //drawHitboxes();

    const auto newSize = size * asteroidSize / spriteInfo.hitboxSize;

    scaleSprite(spriteInfo.sprite, spriteInfo.spriteSize, newSize);
};

void Explosion::update(double deltaTime)
{
    if (spriteInfo.spriteState == spriteInfo.frames.size() - 1) Game::removeEntity(this);

    spriteInfo.spriteLifeTime -= deltaTime;

    if (spriteInfo.spriteLifeTime <= 0) {
        spriteInfo.spriteLifeTime = 0.01;
        spriteInfo.spriteState = (spriteInfo.spriteState + 1) % spriteInfo.frames.size();
        updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteInfo.spriteState);
    }
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