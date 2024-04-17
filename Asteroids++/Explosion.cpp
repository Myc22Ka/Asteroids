#include "Explosion.h"
#include "EntitiesList.h"

Explosion::Explosion(sf::Vector2f position) : Entity(position, 0, 0, 128, sf::Color::Cyan) {
    spriteInfo = getSprite(Sprites::EXPLOSION);
    drawHitboxes();
};

void Explosion::update(float deltaTime)
{
    if (spriteState == spriteInfo.frames.size() - 1) {
        EntitiesList::toRemoveList.push_back(
            std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), this));
    }
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
    if (WindowBox::hitboxesVisibility) window.draw(shape, transform);
}

const EntityType Explosion::getEntityType()
{
    return EntityType::TYPE_EXPLOSION;
}

void Explosion::collisionDetection() {}
