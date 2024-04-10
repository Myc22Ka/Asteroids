#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Score.h"
#include "Sound.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction) : 
    shape(FileMenager::playerData.bullet_size), 
    direction(direction), 
    Entity(position, 0.0f), 
    lifeTime(FileMenager::playerData.bullet_lifetime),
    size((int)FileMenager::playerData.bullet_size >> 1){

    shape.setRadius(size);
    sf::Vector2f center(size, size);

    shape.setOrigin(center);
}

const EntityType Bullet::getEntityType()
{
	return EntityType::TYPE_BULLET;
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

    for (size_t i = 0; i < EntitiesList::entities.size(); i++)
    {
        if (typeid(*EntitiesList::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(EntitiesList::entities[i]);

            if (physics::intersects(position, size, asteroid->position, asteroid->size)) {
                lifeTime = 0;
                EntitiesList::toRemoveList.push_back(
                    std::find(EntitiesList::entities.begin(), EntitiesList::entities.end(), asteroid));
                Score::score += 10;
                playSound(Names::EXPLOSION);
            }
        }
    }
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(shape, sf::Transform().translate(position));
}
