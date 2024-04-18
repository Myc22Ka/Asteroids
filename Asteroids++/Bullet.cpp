#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, const float& angle) :
    direction(direction), 
    Entity(position, angle, 0, FileMenager::playerData.bullet_size, sf::Color::Green),
    lifeTime(FileMenager::playerData.bullet_lifetime){

    spriteInfo = getSprite(Sprites::BULLET);
    setRotation(spriteInfo.sprite, angle);
    damage = 100;
    drawHitboxes();
}

void Bullet::update(float deltaTime)
{
    auto bulletSpeed = FileMenager::playerData.bullet_speed;
    lifeTime -= deltaTime;
    position += sf::Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
    if (lifeTime <= 0) {
        EntitiesList::toRemoveList.push_back(
            std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), this));
    }

    collisionDetection();
}

void Bullet::render(sf::RenderWindow& window)
{
    sf::Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
    if (WindowBox::hitboxesVisibility) window.draw(shape, transform);
}

const EntityType Bullet::getEntityType()
{
    return EntityType::TYPE_BULLET;
}

void Bullet::collisionDetection()
{
    for (size_t i = 0; i < EntitiesList::entities.size(); i++)
    {
        if (typeid(*EntitiesList::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(EntitiesList::entities[i]);

            if (physics::intersects(position, size >> 1, asteroid->position, asteroid->size >> 1) && lifeTime > 0) {
                lifeTime = 0;
                asteroid->health -= damage;

                if (asteroid->health <= 0) {
                    EntitiesList::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));

                    EntitiesList::toRemoveList.push_back(
                        std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), asteroid));

                    Score::score += 10;
                    SoundData::play(Sounds::EXPLOSION);
                }
            }
        }
    }
}