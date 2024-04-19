#include "Bullet.h"
#include "Asteroid.h"
#include "Physics.h"
#include "Score.h"
#include "SoundData.h"

Bullet::Bullet(Vector2f position, Vector2f direction, const float& angle) :
    direction(direction), 
    Entity(position, angle, 0, FileMenager::playerData.bullet_size, Color::Green),
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
    position += Vector2f(direction.x * bulletSpeed * deltaTime, direction.y * bulletSpeed * deltaTime);
    if (lifeTime <= 0) Game::removeEntity(this);

    collisionDetection();
}

void Bullet::render(RenderWindow& window)
{
    Transform transform;
	window.draw(spriteInfo.sprite, transform.translate(position));
    if (Game::hitboxesVisibility) window.draw(shape, transform);
}

const EntityType Bullet::getEntityType()
{
    return EntityType::TYPE_BULLET;
}

void Bullet::collisionDetection()
{
    for (size_t i = 0; i < Game::entities.size(); i++)
    {
        if (typeid(*Game::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);

            if (physics::intersects(position, radius, asteroid->position, asteroid->radius) && lifeTime > 0) {
                lifeTime = 0;
                asteroid->health -= damage;

                if (asteroid->health <= 0) {
                    Game::toAddList.push_back(new Explosion(asteroid->position, asteroid->size));

                    Game::removeEntity(asteroid);

                    Score::score += 10;
                    SoundData::play(Sounds::EXPLOSION);
                }
            }
        }
    }
}