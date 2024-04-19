#include "Explosion.h"

const Sprites EXPLOSIONS[] = { Sprites::EXPLOSION_1, Sprites::EXPLOSION_2, Sprites::EXPLOSION_3, Sprites::EXPLOSION_4 };

Explosion::Explosion(sf::Vector2f position, int asteroidSize) : Entity(position, 0, 0, 256, sf::Color::Cyan) {
    spriteInfo = getSprite(setRandomSprite());
    drawHitboxes();

    const float newSize = size * (static_cast<float>(asteroidSize) / 64);

    scaleSprite(spriteInfo.sprite, spriteInfo.size, newSize);
};

void Explosion::update(float deltaTime)
{
    if (spriteState == spriteInfo.frames.size() - 1) Game::removeEntity(this);

    spriteInfo.spriteLifeTime -= deltaTime;

    if (spriteInfo.spriteLifeTime <= 0) {
        spriteInfo.spriteLifeTime = 0.01;
        spriteState = (spriteState + 1) % spriteInfo.frames.size();
        updateSprite(spriteInfo.sprite, spriteInfo.frames, spriteState);
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
